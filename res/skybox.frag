#version 330 core

in vec3 texCoord0;
out vec4 colour;

uniform samplerCube skybox;

void main()
{
	colour = texture(skybox, texCoord0);
}



