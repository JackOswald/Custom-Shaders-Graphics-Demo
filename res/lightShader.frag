#version 330 core

in vec2 texCoord0;
in vec3 normal0;

uniform sampler2D diffuse;
uniform vec3 v = vec3 (0, 0, 1);

void main()
{
	float lDiff = clamp(dot(-v, normal0), 0.35, 1.0);
	gl_FragColor = texture2D(diffuse, texCoord0) * lDiff;
}



