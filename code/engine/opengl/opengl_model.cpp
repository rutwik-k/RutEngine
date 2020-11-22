//just loading vertices and normals for now, expand to uvs and color later
Model RendererLoadModel(Renderer *renderer, float *data, u32 data_size, u32 vertex_count, char *vertex_source, char *fragment_source){
    Model model = {};
    glGenVertexArrays(1, &model.vao);
    glBindVertexArray(model.vao);
    
    glGenBuffers(1, &model.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, model.vbo);
    
    glBufferData(GL_ARRAY_BUFFER, data_size, 0, GL_DYNAMIC_DRAW);
    
    model.data = data;
    model.data_size = data_size;
    
    for(int i = 0; i < model.data_size / sizeof(f32); i++){
        model.initial_data[i] = data[i];
    }
    
    model.shader = CreateOpenGLShader(vertex_source, fragment_source);
    model.vertex_count = vertex_count;
    
    glUseProgram(model.shader);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(f32), (void *)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
    ShaderLoadMat4(model.shader, renderer->proj, "proj");
    
    return model;
}