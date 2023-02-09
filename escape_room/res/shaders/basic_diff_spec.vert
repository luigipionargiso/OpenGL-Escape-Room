#version 330 core

layout (location=0) in vec4 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;
layout (location=3) in vec3 tangent;

out vec2 v_TexCoord;
out vec3 v_Normal;
out vec3 v_FragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * position;
    v_TexCoord = texCoord;
    v_Normal = mat3(transpose(inverse(u_Model))) * normal; //da fare su cpu; inutile se non ci sono scalamenti non uniformi
    v_FragPos = vec3(u_Model * position);
}
