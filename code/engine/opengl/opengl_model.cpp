//just loading vertices and normals for now, expand to uvs and color later
Model RendererLoadModel(Renderer *renderer, float *data, u32 data_size, u32 vertex_count, Material material){
    Model model = {};
    model.data = data;
    model.data_size = data_size;
    
    for(int i = 0; i < model.data_size / sizeof(f32); i++){
        model.initial_data[i] = data[i];
    }
    
    model.material = material;
    model.vertex_count = vertex_count;
    
    return model;
}