#ifndef _TEXTURE_H
#define _TEXTURE_H
/*This class handles loading textures using the SOIL library*/
#include <iostream>
#include <SOIL.h>
#include <GLFW\glfw3.h>

class Texture
{
public:
	Texture(const char* filename);
	Texture();
	~Texture();
	GLuint getTexture();
private:
	GLuint _texture;
	GLuint loadTexture(const char* filename);
};

#endif