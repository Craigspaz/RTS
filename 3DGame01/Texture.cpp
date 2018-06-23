#include "Texture.h"


Texture::Texture(const char* filename)
{
	_texture = loadTexture(filename);
}
Texture::Texture()
{
	Texture("res/air.png");
}


Texture::~Texture()
{
	
}

GLuint Texture::getTexture()
{
	return _texture;
}

GLuint Texture::loadTexture(const char* filename)
{
	GLuint texture = SOIL_load_OGL_texture(filename, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	return texture;
}
