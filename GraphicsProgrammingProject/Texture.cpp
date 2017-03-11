#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>


Texture::Texture(const std::string& fileName)
{
	int width, height, numOfComponents;
	unsigned char* imageData = stbi_load((fileName).c_str(), &width, &height, &numOfComponents, 4); 
	if (imageData == NULL)
	{
		std::cerr << "Failed to load texture";
	}
	glGenTextures(1, &texture); // Generate buffer to store the texture
	glBindTexture(GL_TEXTURE_2D, texture); // Binds the texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wraps the texture outside width
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wraps the texture outside the height
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear filtering for minification(texture is smaller than the area)
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear filtering for magnification(texture is larger than the area)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_TEXTURE_MAG_FILTER, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);
}

Texture::~Texture()
{
	glDeleteTextures(1, &texture); // Delete our textures
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0 && unit <= 31); // Check we are working with one of the 32 textures
	glActiveTexture(GL_TEXTURE0 + unit); // Set the active texture unit
	glBindTexture(GL_TEXTURE_2D, texture); // Type of texture to bind to unit
}
