#version 330 core
//120
in vec2 texCoord0;
in vec3 normal0;

uniform sampler2D diffuse;

void main()
{

	gl_FragColor = texture2D(diffuse, texCoord0);
}



