#ifndef MODEL_H
#define MODEL_H

struct Model {
    //TODO: Separate into Mesh and Material
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    u32 vertex_count;
    u32 index_count;
    GLuint shader;
};

#endif //MODEL_H
