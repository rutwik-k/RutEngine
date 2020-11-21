#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normals;
//layout (location = 2) in vec2 tex_coords;

uniform mat4 proj;
uniform mat4 view;

out vec3 pass_colour;

void main()
{
   // out_colour = colour;
    //gl_Position = ortho * view * vec4(pos.x, pos.y, pos.z, 1.0);
    gl_Position = proj * view * vec4(pos.x, pos.y, pos.z, 1.0);
	vec3 normalised_normals = normalize(normals);

	//calculate lighting
	float ambient_strength = 0.5;

	vec3 light_pos = vec3(1.2, 10.0, 2.0);
	
	vec3 light_direction = normalize(light_pos - pos);
	vec3 light_colour = vec3(1.0, 1.0, 1.0);
	
	float diff = max(dot(normalised_normals, light_direction), 0.0);
	vec3 diffuse = diff * light_colour;
	
	vec3 cube_colour = vec3(1.0, 0.0, 0.0);

	vec3 ambient = ambient_strength * light_colour;
    pass_colour = (ambient + diffuse) * cube_colour;
	//pass_colour = vec3(1.0, 0.0, 0.0);
}