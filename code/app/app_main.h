/* date = November 20th 2020 7:36 pm */

#ifndef APP_MAIN_H
#define APP_MAIN_H

#include "engine/renderer.h"
#include "engine/camera.h"

struct App{
    Platform *platform;
    
    Renderer renderer;
    Camera camera;
};

global App app = {};

#endif //APP_MAIN_H
