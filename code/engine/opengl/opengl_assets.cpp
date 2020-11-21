Model CreateModel(f32 *data, u32 *indices, u32 vertex_count, u32 index_count, char *vertex, char *fragment){
    Model model = {};
    model.vertex_count = vertex_count;
    model.index_count = index_count;
    
    glGenVertexArrays(1, &model.vao);
    glBindVertexArray(model.vao);
    glGenBuffers(1, &model.vbo);
    
    //position and normals
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * vertex_count, data, GL_STATIC_DRAW);
    
    //indices
    glGenBuffers(1, &model.ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model.ibo);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * index_count, indices, GL_STATIC_DRAW);
    
    
    model.shader = CreateOpenGLShader(vertex, fragment);
    glUseProgram(model.shader);
    
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(f32), (void *)0);
    //normals
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    return model;
}