
#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#define STB_IMAGE_IMPLEMENTATION
#include "ext/stb_image.h"

#define MAX_QUADS_PER_DRAW 5000
#define MAX_DATA_PER_MODEL_BATCH 9 * 50000

#include "opengl_material.h"

//rendering mode
enum{
    FILL,
    WIREFRAME
};

struct Renderer{
    u32 mode; //wireframe or fill
    
    Mat4 view; //camera view
    Mat4 proj; //projection matrix
    Mat4 ortho;
    
    Light light;
    
    /* Quad Batch */
    GLuint quad_vao;
    GLuint quad_vbo;
    GLuint quad_ibo;
    GLuint quad_shader;
    f32 quad_vertex_batch[36 * MAX_QUADS_PER_DRAW];
    u32 quad_index_batch[6 * MAX_QUADS_PER_DRAW];
    u32 quads_submitted;
    
    /* Model Batch */
    //data is a single f32 value.
    GLuint model_vao;
    GLuint model_vbo;
    Material model_material;
    f32 *model_data_batch;
    u32 data_submitted;
    u32 vertices_submitted;
    
    Camera camera;
    
    /*DEBUG STUFF */
    u32 draw_calls;
};


#endif //OPENGL_RENDERER_H
