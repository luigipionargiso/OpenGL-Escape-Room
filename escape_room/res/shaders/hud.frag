#version 330 core

in vec2 v_uv;

uniform sampler2D u_image;

void main()
{
	vec4 sampled = texture( u_image, v_uv );
	gl_FragColor = vec4(sampled.rgb, sampled.a / 2.0);
}