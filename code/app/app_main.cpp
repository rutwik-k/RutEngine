#include "engine/camera.cpp"
#include "engine/renderer.cpp"
#include "engine/audio.cpp"

Model cube;

internal void AppInit(){
    RendererInit(&app.renderer);
    app.camera.pos = Vec3(0, 0, 0);
    app.camera.front = Vec3(0, 0, -1);
    app.camera.up = Vec3(0, 1, 0);
    cube = RendererLoadModel(&app.renderer, CUBE_DATA, sizeof(CUBE_DATA), 36, "cube_vertex.glsl", "cube_fragment.glsl");
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
    RendererDrawModel(&app.renderer, &cube, Vec3(0, 0, 15));
    RendererDrawModel(&app.renderer, &cube, Vec3(1, 0, 3));
    //RendererDrawModel(&app.renderer, &cube, Vec3(2, 0, -11));
    RendererFinish(&app.renderer);
    
    //char log[256];
    //snprintf(log, 256, "(%f, %f, %f)", app.camera.pos.x, app.camera.pos.y, app.camera.pos.z);
    //OutputDebugString(log);
    
    PlatformUpdateInput(app.platform);
}