#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCords;
out vec3 aColor;
out vec2 TexCord;

uniform mat4 transform;

void main()
{
	gl_Position = transform * vec4(aPos.xyz, 1.f);
	aColor = aPos;
	TexCord = aTexCords;
}