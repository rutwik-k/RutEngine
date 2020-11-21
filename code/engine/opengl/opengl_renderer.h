
#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb_image.h"


//rendering mode
enum{
    FILL,
    WIREFRAME
};

struct Renderer{
    u32 mode; //wireframe or fill
    
    Mat4 view; //camera view
    Mat4 proj; //projection matrix
    
    GLuint cube_vao;
    GLuint cube_vbo;
    GLuint cube_shader;
};


#endif //OPENGL_RENDERER_H
