global HDC dc;
global HGLRC opengl_context;

global PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

#define GLProcedure(type, name) PFN##type##PROC name
#include "ext/opengl/opengl_procedures.h"

internal void *Win32LoadOpenGLProcedure(char *procedure){
    void *opengl_proc = wglGetProcAddress(procedure);
    return opengl_proc;
}

internal void Win32LoadOpenGLProcedures(){
#define GLProcedure(type, name) name = (PFN##type##PROC)Win32LoadOpenGLProcedure("" #name)
#include "ext/opengl/opengl_procedures.h"
}

internal b32 Win32InitOpenGL(HWND *hwnd){
    //set the pixel format of the frame buffer
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
        PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
        32,                   // Colordepth of the framebuffer.
        0, 0, 0, 0, 0, 0,
        0,
        0,
        0,
        0, 0, 0, 0,
        24,                   // Number of bits for the depthbuffer
        8,                    // Number of bits for the stencilbuffer
        0,                    // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0, 0, 0
    };
    //get device context
    if(!(dc = GetDC(*hwnd))){
        //device context creation failed
        OutputDebugString("Failed to create device context\n");
        return 0;
    }
    
    i32 pixel_format_number;
    //convert pfd to pixel format number
    if(!(pixel_format_number = ChoosePixelFormat(dc, &pfd))){
        OutputDebugString("Failed to convert pfd to pixel format number\n");
        return 0;
    }
    
    if(!SetPixelFormat(dc, pixel_format_number, &pfd)){
        OutputDebugString("Failed to set pixel format to the dc\n");
        return 0;
    }
    
    //create a dummy context to access wgl extensions
    HGLRC dummy_context;
    if(!(dummy_context = wglCreateContext(dc))){
        OutputDebugString("Failed to create dummy context\n");
        return 0;
    }
    wglMakeCurrent(dc, dummy_context);
    
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)Win32LoadOpenGLProcedure("wglChoosePixelFormatARB");
    
    const int pfd_attribs[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        WGL_SAMPLE_BUFFERS_ARB, 1,
        WGL_SAMPLES_ARB, 4,
        0, // End
    };
    
    i32 pixel_format;
    u32 num_formats;
    
    wglChoosePixelFormatARB(dc, pfd_attribs, NULL, 1, &pixel_format, &num_formats);
    
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)Win32LoadOpenGLProcedure("wglCreateContextAttribsARB");
    
    //opengl context creation
    const int context_attribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
        WGL_CONTEXT_MINOR_VERSION_ARB, 3,
        0
    };
    
    if(!(opengl_context = wglCreateContextAttribsARB(dc, dummy_context, context_attribs))){
        OutputDebugString("Failed to create OpenGL context\n");
        return 0;
    }
    
    wglMakeCurrent(dc, 0);
    wglDeleteContext(dummy_context);
    wglMakeCurrent(dc, opengl_context);
    
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)Win32LoadOpenGLProcedure("wglSwapIntervalEXT");
    
    Win32LoadOpenGLProcedures();
    
    return 1;
}

internal void Win32OpenGLCleanUp(){
    wglMakeCurrent(dc, 0);
    wglDeleteContext(opengl_context);
}

internal void Win32SetVSync(b32 state){
    wglSwapIntervalEXT(state);
}

internal void Win32OpenGLSwapBuffers(){
    wglSwapLayerBuffers(dc, WGL_SWAP_MAIN_PLANE);
}