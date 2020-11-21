#version 330 core
out vec4 frag_colour;

in vec3 pass_normals;
in vec3 pass_vertices;
in vec3 pass_colour;

void main()
{
    frag_colour = vec4(pass_colour, 1.0);
}