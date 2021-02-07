#version 330 core
in vec3 aColor;
out vec4 FrgaColor;

void main()
{
	FrgaColor = vec4(aColor, FrgaColor);
}