#include "engine/camera.cpp"
#include "engine/renderer.cpp"
#include "engine/audio.cpp"

internal void AppInit(){
    RendererInit(&app.renderer);
    app.camera.pos = Vec3(0, 0, -10);
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
    RendererStart(&app.renderer, app.camera.pos);
    RendererDrawCube(&app.renderer);
    RendererFinish(&app.renderer);
}