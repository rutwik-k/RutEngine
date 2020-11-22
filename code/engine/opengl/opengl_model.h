/* date = November 22nd 2020 4:57 pm */

#ifndef OPENGL_MODEL_H
#define OPENGL_MODEL_H

//temporary solution - fix with memory when i implement that
#define MAX_INITIAL_SIZE 512

struct Model{
    GLuint vao;
    GLuint vbo;
    GLuint shader;
    
    f32 *data;
    u32 data_size;
    
    f32 initial_data[MAX_INITIAL_SIZE];
    
    u32 vertex_count;
}

#endif //OPENGL_MODEL_H
