#include "opengl_renderer.h"
#include "opengl_shader.cpp"

#include "engine/primitives.h"

internal void RendererInit(Renderer *renderer){
    glEnable(GL_DEPTH_TEST);
    
    glGenVertexArrays(1, &renderer->cube_vao);
    glBindVertexArray(renderer->cube_vao);
    
    glGenBuffers(1, &renderer->cube_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, renderer->cube_vbo);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(CUBE_DATA), CUBE_DATA, GL_STATIC_DRAW);
    
    renderer->cube_shader = CreateOpenGLShader("cube_vertex.glsl", "cube_fragment.glsl");
    
    glUseProgram(renderer->cube_shader);
    //position
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(f32), (void *)0);
    glEnableVertexAttribArray(0);
    //normal
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(f32), (void *)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
    
    renderer->view = Mat4Identity();
    Mat4Translate(&renderer->view, Vec3(0, 0, 0));
    renderer->proj = CreateProjectionMat4(90.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    ShaderLoadMat4(renderer->cube_shader, renderer->proj, "proj");
    
}

internal void RendererStart(Renderer *renderer, Vec3 camera_pos){
    glClearColor(91.0f / 255.0f, 163.0f / 255.0f, 171.0f / 255.0f, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(renderer->mode == WIREFRAME){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    
    Mat4Translate(&renderer->view, Vec3(-camera_pos.x, camera_pos.y, camera_pos.z));
}

//elements model
internal void RendererDrawCube(Renderer *renderer){
    glUseProgram(renderer->cube_shader);
    glBindVertexArray(renderer->cube_vao);
    ShaderLoadMat4(renderer->cube_shader, renderer->proj, "proj");
    ShaderLoadMat4(renderer->cube_shader, renderer->view, "view");
    glBindBuffer(GL_ARRAY_BUFFER, renderer->cube_vbo);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

internal void RendererFinish(Renderer *renderer){
    
}

