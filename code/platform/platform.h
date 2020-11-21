/* date = November 20th 2020 6:41 pm */
#ifndef PLATFORM_H
#define PLATFORM_H

#define WINDOW_TITLE          "RutEngine"
#define INITIAL_WINDOW_WIDTH  1280
#define INITIAL_WINDOW_HEIGHT 720

#define PERMANENT_MEMORY_SIZE megabytes(512)
#define FRAME_MEMORY_SIZE megabytes(1)

struct Platform {
    /* Window */
    u32 width;
    u32 height;
    
    /* Options */
    b32 should_quit;
    b32 is_initialised;
    b32 vsync;
    
    /* Memory */
    void *permanent_memory; //lasts for the whole app duration
    u32 permanent_memory_size;
    
    void *frame_memory; //lasts one frame
    u32 frame_memory_size;
    
    /* Timing */
    f32 current_time;
    f32 target_fps;
    f32 dt;
    f32 ms_per_frame;
    f32 fps_per_frame;
    
    /* Input Handling */
    b32 key_down[KEY_MAX];
    b32 left_mouse_down;
    b32 left_mouse_pressed;
    b32 right_mouse_down;
    b32 clicked;
    f32 cursor_x;
    f32 cursor_y;
    f32 cursor_dx;
    f32 cursor_dy;
    f32 last_x = INITIAL_WINDOW_WIDTH / 2;
    f32 last_y = INITIAL_WINDOW_HEIGHT / 2;
    
    /* Sound */
    int samples_per_sec;
    int sample_count;
    int channels;
    int bytes_per_sample;
    void *samples;
    
    /* File Handling */
    void *(*PlatformReadEntireFileToString)(char *filename);
    b32   (*PlatformWriteToFile)(char *filename, u64 data_size, void *data);
    void  (*PlatformFreeFile)(void *data);
    
    /* Error Handling */
    void  (*PlatformDisplayError)(char *title, char *info);
};

global Platform platform = {};

void PlatformUpdateInput(Platform *platform){
    platform->left_mouse_pressed = 0;
    platform->cursor_dx = platform->cursor_x - platform->last_x;
    platform->cursor_dy = platform->last_y - platform->cursor_y;
    platform->last_x = platform->cursor_x;
    platform->last_y = platform->cursor_y;
}

#endif //PLATFORM_H
