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
    gl_Position = u_Projection * u_View * u_Model * position;
    v_TexCoord = texCoord;
    v_Normal = mat3(transpose(inverse(u_Model))) * normal; //da fare su cpu; inutile se non ci sono scalamenti non uniformi
    v_FragPos = vec3(u_Model * position);

    /* calculate the transform matrix from tangent space to world space */
    vec3 T = normalize(mat3(u_Model) * tangent);
    vec3 N = v_Normal;
    // re-orthogonalize T with respect to N
    T = normalize(T - dot(T, N) * N);
    // then retrieve perpendicular vector B with the cross product of T and N
    vec3 B = cross(N, T);
    v_TBN = mat3(T, B, N);

    //v_debug = T;
}
