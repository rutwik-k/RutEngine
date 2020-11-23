#version 330 core
out vec4 frag_colour;

in vec3 pass_normals;
in vec3 pass_vertices;
vec3 pass_colour;

uniform vec3 view_pos;

void main()
{
	//calculate lighting
	vec3 light_pos = vec3(1.2, 10.0, 2.0);
	vec3 light_colour = vec3(1.0, 1.0, 1.0);

	float ambient_strength = 0.2;
	vec3 ambient = ambient_strength * light_colour;

	float diffuse_strength = 0.5;
	vec3 normalised_normals = normalize(pass_normals);	
	vec3 light_direction = normalize(light_pos - pass_vertices);
	float diff = max(dot(normalised_normals, light_direction), 0.0);
	vec3 diffuse = diff * light_colour * vec3(diffuse_strength, diffuse_strength, diffuse_strength);

	float specular_strength = 0.5;
	vec3 view_dir = normalize(view_pos - pass_vertices);
	vec3 reflect_dir = reflect(-light_direction, normalised_normals);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 16);
	vec3 specular = specular_strength * spec * light_colour;
	
	vec3 cube_colour = vec3(1.0, 0.0, 0.0);
	pass_colour = (ambient + diffuse + specular) * cube_colour;    

    frag_colour = vec4(pass_colour, 1.0);
	/*if(spec > 0.2){
		frag_colour = vec4(1.0, 1.0, 1.0, 1.0);
	}*/
}