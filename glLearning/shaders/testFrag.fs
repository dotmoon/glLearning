#version 330 core
in vec3 aColor;
in vec2 TexCord;
out vec4 FrgaColor;

uniform sampler2D my_texture;

void main()
{
	//FrgaColor = vec4(aColor, 1.0);
	FrgaColor = texture(my_texture, TexCord);// * vec4(aColor, 1.0);
}