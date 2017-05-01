#version 330 core

layout (location = 0) in vec3 position;

out vec3 texCoord0;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec4 pos = projection * view * vec4(position, 1.0);
	gl_Position = pos.xyww;
	texCoord0 = position;
}
