#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
//layout (location = 2) in vec2 tex_coords;

uniform mat4 proj;
uniform mat4 view;

out vec3 pass_normals;
out vec3 pass_vertices;

void main()
{
	gl_Position = proj * view * vec4(pos.x, pos.y, pos.z, 1.0);
	pass_normals = normals;
	pass_vertices = pos;
}