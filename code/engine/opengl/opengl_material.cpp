Material RendererCreateDefaultMaterial(Renderer *renderer){
    Material material = {};
    material.ambient_strength = 0.5f;
    material.diffuse_strength = 0.5f;
    material.specular_strength = 0.5f;
    material.shader = CreateOpenGLShader("default_vertex.glsl", "default_fragment.glsl");
    glUseProgram(material.shader);
    ShaderLoadMat4(material.shader, renderer->proj, "proj");
    return material;
}