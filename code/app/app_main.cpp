#include "engine/obj_parser.h"

#include "common/memory.cpp"
#include "engine/camera.cpp"
#include "engine/renderer.cpp"
#include "engine/audio.cpp"

Light light;
Material material;
Model cube;
f32 sine_value;

internal void AppInit(){
    app.permanent_arena = MemoryArenaInit((u8 *)platform.permanent_memory, platform.permanent_memory_size);
    RendererInit(&app.renderer);
    app.camera.pos = Vec3(0, 0, 0);
    app.camera.front = Vec3(0, 0, -1);
    app.camera.up = Vec3(0, 1, 0);
    app.camera.target_pos = Vec3(0, 0, 0);
    material = RendererCreateDefaultMaterial(&app.renderer);
    cube = RendererLoadModel(&app.renderer, CUBE_DATA, sizeof(CUBE_DATA), 36, material);
    light.pos = Vec3(1.2f, 10.0f, 2.0f);
    light.colour = Vec3(1.0f, 1.0f, 1.0f);
    sine_value = 0.0f;
}

internal void AppUpdate(Platform *platform){
    app.platform = platform;
    if(!app.platform->is_initialised){
        AppInit();
        app.platform->is_initialised = 1;
    }
    
    if(app.platform->key_down[KEY_1]){
        app.renderer.mode = WIREFRAME;
    }
    if(app.platform->key_down[KEY_2]){
        app.renderer.mode = FILL;
    }
    
    CameraUpdate(&app.camera);
    RendererStart(&app.renderer, app.camera);
    RendererSetLight(&app.renderer, light);
    
    for(int i = 0; i < 32; i++){
        for(int j = 0; j < 32; j++){
            RendererDrawModel(&app.renderer, &light, &cube, Vec3(i * 1, 0, j * 1), Vec3(0.5f, 0.2f, 1.0f));
        }
    }
    RendererDrawModel(&app.renderer, &light, &cube, Vec3(light.pos.x, light.pos.y, light.pos.z), Vec3(1.0f, 1.0f, 1.0f));
    
    RendererDrawQuad(&app.renderer, Vec4(0, 0, 100, 100), Vec4(0.1f, 0.4f, 0.2f, 1.0f));
    RendererFinish(&app.renderer);
    
    light.pos.x += 50.0f * cosf(sine_value * 0.1f) * app.platform->dt;
    light.pos.z += 50.0f * sinf(sine_value * 0.1f) * app.platform->dt;
    sine_value++;
    
    //char log[256];
    //snprintf(log, 256, "(%f, %f, %f)", app.camera.pos.x, app.camera.pos.y, app.camera.pos.z);
    //OutputDebugString(log);
    
    PlatformUpdateInput(app.platform);
}