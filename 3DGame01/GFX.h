#ifndef _GFX_H
#define _GFX_H
/*This is the file with all of the drawing code.*/
#include <stdlib.h>
#include <iostream>
#include <glut.h>
#include <string>
#include <cstring>
#include <GLFW\glfw3.h>
#include <math.h>
#include <cmath>
#include "Texture.h"
class GFX
{
public:
	GFX();
	~GFX();
	
	//2D Functions
	static void drawRect(float x, float y, float xx, float yy, Texture* texture);
	static void drawRect(float x, float y, float xx, float yy);
	static void drawLine(float x, float y, float xx, float yy, Texture* texture);
	static void drawLine(float x, float y, float xx, float yy);
	static void drawString(float x, float y, const char* text, float r, float g, float b);
	static void drawCircle(float x, float y, float r);
	static void drawCircle(float x, float y, float r, Texture* texture);
	//static void drawString(float x, float y, std::string text, float r, float g, float b); // This function is buggy. 

	//3D Functions
	static void drawCube(float x, float y, float z, float xx, float yy, float zz);
	static void drawCube(float x, float y, float z, float xx, float yy, float zz, Texture* texture);
	static void drawGrass(float x, float y, float z, float xx, float yy, float zz, Texture* texture, Texture* top, Texture* bottom);
	static void drawTestCube(float x, float y, float z, float xx, float yy, float zz, Texture* texture);
	static void drawGrassTest(float x, float y, float z, float xx, float yy, float zz, Texture* texture, Texture* top, Texture* bottom);
	static void drawCubeFromCorner(float xx, float yy, float zz, Texture* texture);
	static void drawGrass(float xx, float yy, float zz, Texture* texture, Texture* top, Texture* bottom);
};

#endif