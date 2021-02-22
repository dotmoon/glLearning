#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCords;
out vec3 aColor;
out vec2 TexCord;

void main()
{
	gl_Position = vec4(aPos, 1.f);
	aColor = aPos;
	TexCord = aTexCords;
}