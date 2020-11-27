/* date = November 25th 2020 8:26 pm */

#ifndef OPENGL_MATERIAL_H
#define OPENGL_MATERIAL_H

struct Material{
    GLuint shader;
    float ambient_strength;
    float diffuse_strength;
    float specular_strength;
};

#endif //OPENGL_MATERIAL_H
