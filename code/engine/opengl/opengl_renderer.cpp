#include "opengl_renderer.h"
#include "opengl_model.h"

#include "opengl_shader.cpp"
#include "opengl_material.cpp"
#include "opengl_model.cpp"

#include "engine/primitives.h"

internal void RendererInit(Renderer *renderer){
    /* Quad Setup */
    glGenVertexArrays(1, &renderer->quad_vao);
    glBindVertexArray(renderer->quad_vao);
    
    //fill vbo with 0s
    glGenBuffers(1, &renderer->quad_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(renderer->quad_vertex_batch), NULL, GL_DYNAMIC_DRAW);
    
    glGenBuffers(1, &renderer->quad_ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->quad_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(renderer->quad_index_batch), NULL, GL_DYNAMIC_DRAW);
    
    renderer->quad_shader = CreateOpenGLShader("quad_vertex.glsl", "quad_fragment.glsl");
    glUseProgram(renderer->quad_shader);
    
    renderer->model_data_batch = (f32 *)MemoryArenaAllocate(&app.permanent_arena, MAX_DATA_PER_MODEL_BATCH * sizeof(f32));
    
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(f32), (void*)0);
    glEnableVertexAttribArray(0);
    //colour
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
    //texture
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(f32), (void *)(7 * sizeof(f32)));
    glEnableVertexAttribArray(2);
    /* ------------- */
    
    /* Model Setup */
    glGenVertexArrays(1, &renderer->model_vao);
    glBindVertexArray(renderer->model_vao);
    
    //fill vbo with 0s
    glGenBuffers(1, &renderer->model_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->model_vbo);
    glBufferData(GL_ARRAY_BUFFER, MAX_DATA_PER_MODEL_BATCH * sizeof(f32), NULL, GL_DYNAMIC_DRAW);
    
    renderer->model_material = RendererCreateDefaultMaterial(renderer);
    glUseProgram(renderer->model_material.shader);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 9 * sizeof(f32), (void *)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 9 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
    //colour
    glVertexAttribPointer(2, 3, GL_FLOAT, false, 9 * sizeof(f32), (void *)(6 * sizeof(f32)));
    glEnableVertexAttribArray(2);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    renderer->view = Mat4Identity();
    renderer->proj = CreateProjectionMat4(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    renderer->ortho = CreateOrthographicMat4(0, INITIAL_WINDOW_WIDTH, 0, INITIAL_WINDOW_HEIGHT, -1.0f, 100.0f);
}

internal void RendererStart(Renderer *renderer, Camera camera){
    glClearColor(22.0f / 255.0f, 23.0f / 255.0f, 23.0f / 255.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    renderer->camera = camera;
    
    if(renderer->mode == WIREFRAME){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    renderer->view = Mat4LookAt(camera.pos, camera.pos + camera.front, camera.up);
    
    {   /* Quad Data */
        renderer->quads_submitted = 0;
        glUseProgram(renderer->quad_shader);
        glBindVertexArray(renderer->quad_vao);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 0, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->quad_ibo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, 0, 0);
    }
    
    {   /* Model Data */
        renderer->data_submitted = 0;
        renderer->vertices_submitted = 0;
        glUseProgram(renderer->model_material.shader);
        glBindVertexArray(renderer->model_vao);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->model_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, 0, 0);
    }
    
    renderer->draw_calls = 0;
}

internal void RendererSetLight(Renderer *renderer, Light light){
    renderer->light = light;
}

internal void RendererDrawQuadBatch(Renderer *renderer){
    if(renderer->quads_submitted > 0){
        glUseProgram(renderer->quad_shader);
        glBindVertexArray(renderer->quad_vao);
        
        glBindBuffer(GL_ARRAY_BUFFER, renderer->quad_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->quads_submitted * sizeof(QUAD_DATA), renderer->quad_vertex_batch);
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer->quad_ibo);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, renderer->quads_submitted * sizeof(QUAD_INDICES), renderer->quad_index_batch);
        
        ShaderLoadMat4(renderer->quad_shader, renderer->ortho, "ortho");
        
        glDrawElements(GL_TRIANGLES, renderer->quads_submitted * (sizeof(QUAD_INDICES)/sizeof(u32)), GL_UNSIGNED_INT, 0);
    }
    renderer->quads_submitted = 0;
}

internal void RendererDrawModelBatch(Renderer *renderer){
    if(renderer->data_submitted > 0){
        glUseProgram(renderer->model_material.shader);
        glBindVertexArray(renderer->model_vao);
        glBindBuffer(GL_ARRAY_BUFFER, renderer->model_vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, renderer->data_submitted * sizeof(f32), renderer->model_data_batch);
        
        ShaderLoadMat4(renderer->model_material.shader, renderer->view, "view");
        ShaderLoadMat4(renderer->model_material.shader, renderer->proj, "proj");
        ShaderLoadVec3(renderer->model_material.shader, renderer->camera.pos, "view_pos");
        ShaderLoadVec3(renderer->model_material.shader, renderer->light.pos, "light_pos");
        ShaderLoadVec3(renderer->model_material.shader, renderer->light.colour, "light_colour");
        ShaderLoadFloat(renderer->model_material.shader, renderer->model_material.ambient_strength, "ambient_strength");
        ShaderLoadFloat(renderer->model_material.shader, renderer->model_material.diffuse_strength, "diffuse_strength");
        ShaderLoadFloat(renderer->model_material.shader, renderer->model_material.specular_strength, "specular_strength");
        glDrawArrays(GL_TRIANGLES, 0, renderer->vertices_submitted);
        renderer->draw_calls++;
    }
    renderer->data_submitted = 0;
    renderer->vertices_submitted = 0;
}

internal void RendererSubmitQuad(Renderer *renderer, Mat4 trans, Vec4 color){
    if(renderer->quads_submitted >= MAX_QUADS_PER_DRAW){
        RendererDrawQuadBatch(renderer);
    }
    for(int i = 0; i < 4; i++){
        f32 vert_x = QUAD_DATA[i * 9];
        f32 vert_y = QUAD_DATA[i * 9 + 1];
        f32 vert_z = QUAD_DATA[i * 9 + 2];
        
        f32 color_r = QUAD_DATA[i * 9 + 3] * color.r;
        f32 color_g = QUAD_DATA[i * 9 + 4] * color.g;
        f32 color_b = QUAD_DATA[i * 9 + 5] * color.b;
        f32 color_a = QUAD_DATA[i * 9 + 6] * color.a;
        
        f32 texture_x = QUAD_DATA[i * 9 + 7];
        f32 texture_y = QUAD_DATA[i * 9 + 8];
        
        Vec4 vertex_pos = trans * Vec4(vert_x, vert_y, vert_z, 1.0f);
        
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9)] = vertex_pos.x;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 1] = vertex_pos.y;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 2] = vertex_pos.z;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 3] = color_r;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 4] = color_g;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 5] = color_b;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 6] = color_a;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 7] = texture_x;
        renderer->quad_vertex_batch[(36 * renderer->quads_submitted) + (i * 9) + 8] = texture_y;
    }
    
    for(int i = 0; i < 6; i++){
        renderer->quad_index_batch[(6 * renderer->quads_submitted) + i] = QUAD_INDICES[i] + (4 * renderer->quads_submitted);
    }
    
    renderer->quads_submitted++;
}

internal void RendererSubmitModel(Renderer *renderer, Model *model, Mat4 transform, Vec3 colour){
    if(renderer->data_submitted + (model->data_size / sizeof(f32)) >= MAX_DATA_PER_MODEL_BATCH){
        RendererDrawModelBatch(renderer);
    }
    Mat4 normal_mat = transform;
    
    for(int i = 0; i < model->vertex_count; i++){
        f32 vert_x = model->initial_data[i * 9];
        f32 vert_y = model->initial_data[i * 9 + 1];
        f32 vert_z = model->initial_data[i * 9 + 2];
        f32 norm_x = model->initial_data[i * 9];
        f32 norm_y = model->initial_data[i * 9 + 1];
        f32 norm_z = model->initial_data[i * 9 + 2];
        
        Vec4 vertex_pos = transform * Vec4(vert_x, vert_y, vert_z, 1.0f);
        Mat4Inverse(&normal_mat);
        Mat4Transpose(&normal_mat);
        Vec3 normal_pos = Mat3(normal_mat) * Vec3(norm_x, norm_y, norm_z);
        
        renderer->model_data_batch[renderer->data_submitted++] = vertex_pos.x;
        renderer->model_data_batch[renderer->data_submitted++] = vertex_pos.y;
        renderer->model_data_batch[renderer->data_submitted++] = vertex_pos.z;
        renderer->model_data_batch[renderer->data_submitted++] = normal_pos.x;
        renderer->model_data_batch[renderer->data_submitted++] = normal_pos.y;
        renderer->model_data_batch[renderer->data_submitted++] = normal_pos.z;
        renderer->model_data_batch[renderer->data_submitted++] = colour.r;
        renderer->model_data_batch[renderer->data_submitted++] = colour.g;
        renderer->model_data_batch[renderer->data_submitted++] = colour.b;
        
        renderer->vertices_submitted++;
    }
}

internal void RendererDrawQuad(Renderer *renderer, Vec4 position_and_scale, Vec4 colour){
    Mat4 scale_mat = Mat4Identity();
    Mat4 translate_mat = Mat4Identity();
    
    Mat4Scale(&scale_mat, Vec3(position_and_scale.z, position_and_scale.w, 1.0f));
    Mat4Translate(&translate_mat, Vec3(position_and_scale.x, position_and_scale.y, 0.0f));
    Mat4 transform = translate_mat * scale_mat;
    RendererSubmitQuad(renderer, transform, colour);
}

internal void RendererDrawModel(Renderer *renderer, Light *light, Model *model, Vec3 pos, Vec3 colour){
    //todo - add scaling
    Mat4 transform = Mat4Identity();
    Mat4Translate(&transform, pos);
    RendererSubmitModel(renderer, model, transform, colour);
}

internal void RendererFinish(Renderer *renderer){
    RendererDrawQuadBatch(renderer);
    RendererDrawModelBatch(renderer);
}

