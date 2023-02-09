#version 330 core

layout (location=0) in vec4 position;
layout (location=1) in vec3 normal;
layout (location=2) in vec2 texCoord;
layout (location=3) in vec3 tangent;

out vec2 v_TexCoord;
out vec3 v_FragPos;
out vec3 v_Normal;
flat out mat3 v_TBN;
out vec3 v_debug;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
    vec4 pos = u_Model * position;
    gl_Position = vec4(pos.x, pos.y, -1.0, 1.0);
}
