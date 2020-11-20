internal void AppInit(){
    OutputDebugString("Initialised App!");
}

internal void AppUpdate(Platform *platform){
    app.platform = platform;
    if(!app.platform->is_initialised){
        AppInit();
        app.platform->is_initialised = 1;
    }
    
    glClearColor(91.0f / 255.0f, 163.0f / 255.0f, 171.0f / 255.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}