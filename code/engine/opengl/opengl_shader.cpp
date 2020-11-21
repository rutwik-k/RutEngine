internal GLuint CreateOpenGLShader(char *vertex_source_file, char *fragment_source_file){
    char *vertex_source = (char *)app.platform->PlatformReadEntireFileToString(vertex_source_file);
    
    char *fragment_source = (char *) app.platform->PlatformReadEntireFileToString(fragment_source_file);
    
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, NULL);
    glCompileShader(vertex_shader);
    
    int  success_v;
    char info_v[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success_v);
    
    if(!success_v){
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_v);
        app.platform->PlatformDisplayError(vertex_source_file, info_v);
    }
    
    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, NULL);
    glCompileShader(fragment_shader);
    
    int  success_f;
    char info_f[512];
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success_f);
    
    if(!success_f){
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_f);
        app.platform->PlatformDisplayError(fragment_source_file, info_f);
    }
    
    GLuint shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);
    
    int  success_p;
    char info_p[512];
    glGetProgramiv(shader_program, GL_LINK_STATUS, &success_p);
    
    if(!success_p){
        glGetProgramInfoLog(shader_program, 512, NULL, info_p);
        app.platform->PlatformDisplayError("Shader Program - Linking error", info_p);
    }
    
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
    return shader_program;
}

internal void ShaderLoadMat4(GLuint shader, Mat4 mat4, char *variable_name){
    u32 mat4_location = glGetUniformLocation(shader, variable_name);
    glUniformMatrix4fv(mat4_location, 1, GL_FALSE, &mat4.elements[0][0]);
}

internal void ShaderLoadVec3(GLuint shader, Vec3 vec3, char *variable_name){
    u32 vec3_location = glGetUniformLocation(shader, variable_name);
    glUniform3f(vec3_location, vec3.x, vec3.y, vec3.z);
}

internal void ShaderLoadFloat(GLuint shader, f32 f, char *variable_name){
    u32 float_location = glGetUniformLocation(shader, variable_name);
    glUniform1f(float_location, f);
}