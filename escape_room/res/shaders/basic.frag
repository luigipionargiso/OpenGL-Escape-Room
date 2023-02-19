#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
	sampler2D normal;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutoff;
	vec3 diffuse_col;
    vec3 specular_col;
};

struct PointLight {
    vec3 position;
    vec3 diffuse_col;
    vec3 specular_col;
};

in vec2 v_tex_coord;
in vec3 v_frag_pos;
in vec3 v_normal;
flat in mat3 v_TBN;

uniform vec3 u_view_pos;
uniform Material u_material;

uniform vec3 u_ambient;
uniform PointLight u_point;
uniform SpotLight u_spot;

vec3 CalculateNormal();
vec3 CalculateSpotLight(vec3 normal);
vec3 CalculatePointLight(vec3 normal);

void main()
{
	/* ambient light */
	vec3 ambient = u_ambient * (texture(u_material.diffuse, v_tex_coord)).rgb;

	vec3 normal = CalculateNormal();

	/* spot light */
	vec3 spotlight = CalculateSpotLight(normal);

	/* point light */
	vec3 pointlight = CalculatePointLight(normal);

	gl_FragColor = vec4(ambient + spotlight + pointlight, 1.0);
}

vec3 CalculateNormal()
{
	/* sample normal map */
	vec3 normal_encoded = texture(u_material.normal, v_tex_coord).rgb;
	vec3 normal = normal_encoded * 2.0 - 1.0;  
	
	/* tranform from tangent space to world space */
	normal = normalize(v_TBN * normal);

	float normal_map_strenght = 1.0;
	return  v_normal * (1.0 - normal_map_strenght) + normal * normal_map_strenght;
}


vec3 CalculateSpotLight(vec3 normal)
{
	/* attenuation */
	float dist = length(u_spot.position - v_frag_pos);
	float attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * (dist * dist));

    vec3 light_to_frag = normalize(v_frag_pos - u_spot.position);
    float factor = dot(light_to_frag, u_spot.direction);

    if (factor > u_spot.cutoff)
	{
		/* diffuse */
		vec3 frag_to_light = -light_to_frag;
		vec3 diffuse = max(dot(normal, frag_to_light), 0.0) *
					u_spot.diffuse_col *
					(texture(u_material.diffuse, v_tex_coord)).rgb; 

		/* specular */
		float specular_strength = 0.2;
		vec3 view_dir = normalize(u_view_pos - v_frag_pos);
		vec3 reflect_dir = reflect(light_to_frag, normal);
		vec3 specular = specular_strength *
						pow(max(dot(view_dir, reflect_dir), 0.0), 32 * (1.0 - texture(u_material.specular, v_tex_coord)).r) *
						u_spot.specular_col;

		vec3 spotlight = (diffuse + specular) * attenuation;
        return spotlight * (factor - u_spot.cutoff)/(1.0 - u_spot.cutoff);
    }
    else
	{
        return vec3(0.0);
    }
}


vec3 CalculatePointLight(vec3 normal)
{
	/* attenuation */
	float dist = length(u_point.position - v_frag_pos);
	float attenuation = 1.0 / (1.0 + 0.09 * dist + 0.032 * (dist * dist));

	/* diffuse */
	vec3 light_dir = normalize(u_point.position - v_frag_pos);
	vec3 diffuse = max(dot(normal, light_dir), 0.0) *
					u_point.diffuse_col *
					(texture(u_material.diffuse, v_tex_coord)).rgb; 

	/* specular */
	float specular_strength = 0.2;
	vec3 view_dir = normalize(u_view_pos - v_frag_pos);
	vec3 reflect_dir = reflect(-light_dir, normal);
	vec3 specular = specular_strength *
					pow(max(dot(view_dir, reflect_dir), 0.0), 32 * (1.0 - texture(u_material.specular, v_tex_coord)).r) *
					u_point.specular_col;

	return (diffuse + specular) * attenuation;
}