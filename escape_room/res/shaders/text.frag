#version 330 core

in vec2 v_uv;

uniform sampler2D u_text_texture;

void main()
{
	gl_FragColor = texture( u_text_texture, v_uv );
}