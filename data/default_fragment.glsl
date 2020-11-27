#version 330 core
out vec4 frag_colour;

in vec3 pass_normals;
in vec3 pass_vertices;
in vec3 pass_colour;

uniform vec3 view_pos;
uniform vec3 light_pos;
uniform vec3 light_colour;

uniform float ambient_strength;
uniform float diffuse_strength;
uniform float specular_strength;

void main()
{
	vec3 ambient = ambient_strength * light_colour;

	vec3 normalised_normals = normalize(pass_normals);	
	vec3 light_direction = normalize(light_pos - pass_vertices);
	float diff = max(dot(normalised_normals, light_direction), 0.0);
	vec3 diffuse = diff * light_colour * vec3(diffuse_strength, diffuse_strength, diffuse_strength);

	vec3 view_dir = normalize(view_pos - pass_vertices);
	vec3 reflect_dir = reflect(-light_direction, normalised_normals);
	float spec = pow(max(dot(view_dir, reflect_dir), 0.0), 16);
	vec3 specular = specular_strength * spec * light_colour;
	
	vec3 final_colour = (ambient + diffuse + specular) * pass_colour;    

    frag_colour = vec4(final_colour, 1.0);
}