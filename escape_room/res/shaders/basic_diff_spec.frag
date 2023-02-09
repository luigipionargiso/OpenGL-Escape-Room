#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_FragPos;

uniform vec3 u_ViewPos;
uniform Material u_Material;
uniform Light u_Light;

void main()
{
	/* attenuation */
	float distance    = length(u_Light.position - v_FragPos);
	float attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * (distance * distance));

	/* ambient light */
	float ambient_strength = 0.3;
	vec3 ambient = ambient_strength *
					u_Light.ambient *
					(texture(u_Material.diffuse, v_TexCoord)).rgb;

	/* diffuse light */
	vec3 norm = normalize(v_Normal);
	vec3 lightDir = normalize(u_Light.position - v_FragPos);
	vec3 diffuse = max(dot(norm, lightDir), 0.0) *
					u_Light.diffuse *
					attenuation *
					(texture(u_Material.diffuse, v_TexCoord)).rgb; 

	/* specular light */
	float specular_strength = 0.4;
	vec3 viewDir = normalize(u_ViewPos - v_FragPos);
	vec3 reflectDir = reflect(-lightDir, norm); 
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specular_strength *
					spec *
					u_Light.specular *
					attenuation *
					(texture(u_Material.specular, v_TexCoord)).rgb;

	vec3 light = ambient + diffuse + specular;
	gl_FragColor =  vec4(light, 1.0);
}
