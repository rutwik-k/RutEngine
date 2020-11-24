#include "opengl_renderer.h"
#include "opengl_model.h"

#include "opengl_shader.cpp"
#include "opengl_model.cpp"

#include "engine/primitives.h"

internal void RendererInit(Renderer *renderer){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    renderer->view = Mat4Identity();
    renderer->proj = CreateProjectionMat4(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
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
}

//elements model
internal void RendererDrawModel(Renderer *renderer, Light *light, Model *model, Vec3 pos, Vec3 colour){
    glUseProgram(model->shader);
    glBindVertexArray(model->vao);
    
    Mat4 translate_mat = Mat4Identity();
    Mat4Translate(&translate_mat, pos);
    Mat4 normal_mat = translate_mat;
    
    for(int i = 0; i < model->vertex_count; i++){
        f32 vert_x = model->initial_data[i * 9];
        f32 vert_y = model->initial_data[i * 9 + 1];
        f32 vert_z = model->initial_data[i * 9 + 2];
        f32 norm_x = model->initial_data[i * 9];
        f32 norm_y = model->initial_data[i * 9 + 1];
        f32 norm_z = model->initial_data[i * 9 + 2];
        
        Vec4 vertex_pos = translate_mat * Vec4(vert_x, vert_y, vert_z, 1.0f);
        Mat4Inverse(&normal_mat);
        Mat4Transpose(&normal_mat);
        Vec3 normal_pos = Mat3(normal_mat) * Vec3(norm_x, norm_y, norm_z);
        
        model->data[i * 9] = vertex_pos.x;
        model->data[i * 9 + 1] = vertex_pos.y;
        model->data[i * 9 + 2] = vertex_pos.z;
        model->data[i * 9 + 3] = normal_pos.x;
        model->data[i * 9 + 4] = normal_pos.y;
        model->data[i * 9 + 5] = normal_pos.z;
        model->data[i * 9 + 6] = colour.r;
        model->data[i * 9 + 7] = colour.g;
        model->data[i * 9 + 8] = colour.b;
    }
    glBindBuffer(GL_ARRAY_BUFFER, model->vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, model->data_size, model->data);
    
    ShaderLoadMat4(model->shader, renderer->proj, "proj");
    ShaderLoadMat4(model->shader, renderer->view, "view");
    ShaderLoadVec3(model->shader, renderer->camera.pos, "view_pos");
    ShaderLoadVec3(model->shader, light->pos, "light_pos");
    ShaderLoadVec3(model->shader, light->colour, "light_colour");
    glDrawArrays(GL_TRIANGLES, 0, model->vertex_count);
}

internal void RendererFinish(Renderer *renderer){
    
}

