#include "engine/light.h"

#include "engine/camera.cpp"
#include "engine/renderer.cpp"
#include "engine/audio.cpp"

Light light;
Model cube;
f32 sine_value;

internal void AppInit(){
    RendererInit(&app.renderer);
    app.camera.pos = Vec3(0, 0, 0);
    app.camera.front = Vec3(0, 0, -1);
    app.camera.up = Vec3(0, 1, 0);
    cube = RendererLoadModel(&app.renderer, CUBE_DATA, sizeof(CUBE_DATA), 36, "cube_vertex.glsl", "cube_fragment.glsl");
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
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            RendererDrawModel(&app.renderer, &light, &cube, Vec3(i * 1.5, 0, j * 1.5), Vec3(0.5f, 0.2f, 1.0f));
        }
    }
    RendererDrawModel(&app.renderer, &light, &cube, Vec3(light.pos.x, light.pos.y, light.pos.z), Vec3(1.0f, 1.0f, 1.0f));
    RendererFinish(&app.renderer);
    
    light.pos.x += 50.0f * sinf(sine_value * 0.1f) * app.platform->dt;
    sine_value++;
    
    //char log[256];
    //snprintf(log, 256, "(%f, %f, %f)", app.camera.pos.x, app.camera.pos.y, app.camera.pos.z);
    //OutputDebugString(log);
    
    PlatformUpdateInput(app.platform);
}