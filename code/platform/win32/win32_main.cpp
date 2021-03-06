/* Windows/CRT libraries and headers */
#include <windows.h>
#include <dsound.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

/* My headers */
#include "common/types_and_defines.h"
#include "common/maths.h"

#include "platform/platform_key_list.h"
#include "platform/platform.h"

/* Win32 files */
#include "platform/win32/win32_timer.h"

#include "platform/win32/win32_input.cpp"
#include "platform/win32/win32_error.cpp"
#include "platform/win32/win32_file_io.cpp"
#include "platform/win32/win32_timer.cpp"
#include "platform/win32/win32_dsound.cpp"
#if RENDERER_OPENGL == 1
#include <gl/gl.h>
#include "ext/opengl/glext.h"
#include "ext/opengl/wglext.h"
#include "platform/win32/win32_opengl.cpp"
#endif

#include "app/app_main.h"
#include "app/app_main.cpp"

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nShowCmd){
    /* Win32 Window Initialisation */
    WNDCLASS wc = {};
    wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = Win32WindowProcedure; //handle to event procedure
    wc.hInstance = hInstance; //handle to app instance
    wc.lpszClassName = WINDOW_TITLE " Class"; //window class name
    wc.hCursor = LoadCursorA(hInstance, IDC_ARROW);
    
    RegisterClass(&wc); //registers window class with OS
    
    HWND hwnd = CreateWindowEx(0,                              // Optional window styles.
                               wc.lpszClassName,               // Window class
                               WINDOW_TITLE,                  // Window text
                               WS_OVERLAPPEDWINDOW,            // Window style
                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT,
                               NULL,       // Parent window
                               NULL,       // Menu
                               hInstance, // Instance handle
                               NULL);        // Additional application data
    
    RECT window_rect;
    GetWindowRect(hwnd, &window_rect);
    SetCursorPos(window_rect.right - (INITIAL_WINDOW_WIDTH / 2), window_rect.bottom - (INITIAL_WINDOW_HEIGHT / 2));
    
    if(hwnd == NULL){
        OutputDebugString("Failed to create window.\n");
        return 0;
    }
    
    ShowWindow(hwnd, nShowCmd);
    
    MSG msg = {};
    POINT cursor_pos = {};
    /* ------------------------ */
    
    /* Win32 OpenGL Context Initialisation */
#if RENDERER_OPENGL == 1
    if(!Win32InitOpenGL(&hwnd)){
        OutputDebugString("Failed to initialise OpenGL.\n");
        return 1;
    }
    Win32SetVSync(1);
#endif
    /* ------------------------ */
    
    /* Platform Code Initialisation */
    platform.should_quit = 0;
    platform.is_initialised = 0;
    platform.target_fps = 60.0f;
    platform.dt = 1 / platform.target_fps;
    
    platform.permanent_memory_size = PERMANENT_MEMORY_SIZE;
    platform.permanent_memory = VirtualAlloc(0, platform.permanent_memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    
    platform.frame_memory_size = FRAME_MEMORY_SIZE;
    platform.frame_memory = VirtualAlloc(0, platform.frame_memory_size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    
    platform.PlatformReadEntireFileToString = Win32ReadEntireFileToString;
    platform.PlatformFreeFile = Win32FreeFile;
    platform.PlatformWriteToFile = Win32WriteToFile;
    
    platform.PlatformDisplayError = Win32DisplayError;
    /* ------------------------ */
    
    /* Win32 Timer Initialisation */
    Win32Timer timer = {};
    Win32TimerInit(&timer);
    /* ------------------------- */
    
    /* Win32 Sound Initialisation */
    Win32Sound win32_sound = {};
    platform.samples_per_sec = 48000;
    platform.bytes_per_sample = 2 * sizeof(i16);
    platform.channels = 2;
    Win32InitSound(hwnd, &win32_sound);
    Win32ClearSoundBuffer(&win32_sound);
    //Win32FillSoundBuffer(&win32_sound);
    
    while(!platform.should_quit){
        Win32TimerBegin(&timer);
        while(PeekMessageA(&msg, hwnd, 0, 0, PM_REMOVE)){
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        Win32UpdateScreenCursor(hwnd, cursor_pos, &platform);
        
        AppUpdate(&platform);
        
        Win32OpenGLSwapBuffers();
        Win32TimerEnd(&timer, platform);
    }
    Win32OpenGLCleanUp();
    
    return 0;
}