#version 330 core

in vec2 oTexCord;

out vec4 TexColor;

uniform sampler2D my_texture;

void main()
{
	TexColor = texture(my_texture, oTexCord);
}