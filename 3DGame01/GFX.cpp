#include "GFX.h"


GFX::GFX()
{
}


GFX::~GFX()
{
}

//void GFX::drawString(float x, float y, std::string text, float r, float g, float b)
//{
//	/const char* str = text.c_str();
//	//glPushMatrix();
//	glRasterPos2f(x, y);
//	glColor4f(r, g, b, 1.0);
//	glDisable(GL_TEXTURE);
//	glDisable(GL_TEXTURE_2D);
//	for (int i = 0; i < sizeof(str); i++)
//	{
//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)str[i]);
//	}
//	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_TEXTURE);
//	//glPopMatrix();
//}

void GFX::drawString(float x, float y, const char* text, float r, float g, float b)
{
	//glPushMatrix();
	int len;
	glRasterPos2f(x, y);
	glColor4f(r, g, b, 1.0);
	glDisable(GL_TEXTURE);
	glDisable(GL_TEXTURE_2D);
	len = strlen(text);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_TEXTURE);
	//glPopMatrix();
}


void GFX::drawRect(float x, float y, float xx, float yy, Texture* texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glPushMatrix();
	//glTranslatef(xx,yy,0);
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex2f(xx, yy);
	glTexCoord2f(0, 1);
	glVertex2f(xx, y + yy);
	glTexCoord2f(1, 1);
	glVertex2f(x + xx, y + yy);
	glTexCoord2f(1, 0);
	glVertex2f(x + xx, yy);

	glEnd();
	glPopMatrix();
}
void GFX::drawRect(float x, float y, float xx, float yy)
{
	glPushMatrix();
	//glTranslatef(xx,yy,0);
	glBegin(GL_QUADS);

	glVertex2f(xx, yy);
	glVertex2f(xx, y + yy);
	glVertex2f(x + xx, y + yy);
	glVertex2f(x + xx, yy);

	glEnd();
	glPopMatrix();
}
void GFX::drawLine(float x, float y, float xx, float yy, Texture* texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glPushMatrix();
	glBegin(GL_LINES);
	glTexCoord2f(0, 0);
	glVertex2f(x, y);
	glTexCoord2f(1, 1);
	glVertex2f(xx, yy);
	glEnd();
	glPopMatrix();
}
void GFX::drawLine(float x, float y, float xx, float yy)
{
	glPushMatrix();
	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(xx, yy);
	glEnd();
	glPopMatrix();
}



void GFX::drawCircle(float x, float y, float r)
{
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float degInRads = i * (3.14159265358979323846 / 180.0f);
		glVertex2f((cos(degInRads) * r) + x, (sin(degInRads) * r) + y);
	}
	glEnd();
	glPopMatrix();
}
void GFX::drawCircle(float x, float y, float r, Texture* texture)
{
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float degInRads = i * (3.14159265358979323846 / 180.0f);
		if (i == 0)
		{
			glTexCoord2f(1, 1);
		}
		else if (i == 3.14159265358979323846/2.0f)
		{
			glTexCoord2f(0, 1);
		}
		else if (i == 3.14159265358979323846)
		{
			glTexCoord2f(0, 0);
		}
		else if (i == (3 * 3.14159265358979323846) / 4)
		{
			glTexCoord2f(1, 0);
		}
		glVertex2f((cos(degInRads) * r) + x, (sin(degInRads) * r) + y);
	}
	glEnd();
	glPopMatrix();
}

void GFX::drawCube(float x, float y, float z, float xx, float yy, float zz)
{
	//glLoadIdentity();
	glTranslatef(xx, yy, zz);
	glPushMatrix();
	glBegin(GL_QUADS);
	//Front face
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, -y, z);
	//Backface
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, -y, -z);
	//Bottumface
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-x, -y, -z);
	glVertex3f(-x, -y, z);
	glVertex3f(-x, y, z);
	glVertex3f(-x, y, -z);
	//Top Face
	glColor3f(1.0f, 0.0f, 1.0f);
	glVertex3f(x, -y, -z);
	glVertex3f(x, -y, z);
	glVertex3f(x, y, z);
	glVertex3f(x, y, -z);

	glColor3f(0.75f, 0.05f, 0.05f);
	glVertex3f(-x, -y, -z);
	glVertex3f(x, -y, -z);
	glVertex3f(x, -y, z);
	glVertex3f(-x, -y, z);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(-x, y, -z);
	glVertex3f(x, y, -z);
	glVertex3f(x, y, z);
	glVertex3f(-x, y, z);
	glEnd();
	glPopMatrix();
}
void GFX::drawCube(float x, float y, float z, float xx, float yy, float zz, Texture* texture){
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	//glLoadIdentity();
	glTranslatef(xx, yy, zz);
	glPushMatrix();
	glBegin(GL_QUADS);
	//Front face
	//glColor3f(1f,0f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1, 0);
	glVertex3f(-x, y, z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(x, -y, z);
	//Backface
	//glColor3f(0f,1f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1, 0);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, -z);
	glTexCoord2f(0, 1);
	glVertex3f(x, -y, -z);
	//left
	//glColor3f(0f,0f,1f);
	glTexCoord2f(0, 1);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1, 0);
	glVertex3f(-x, y, z);
	glTexCoord2f(0, 0);
	glVertex3f(-x, y, -z);
	//right
	//glColor3f(1f,0f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(x, -y, -z);
	glTexCoord2f(0, 1);
	glVertex3f(x, -y, z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(1, 0);
	glVertex3f(x, y, -z);

	//Bottom Face
	//glColor3f(.75f,.05f,.05f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1, 0);
	glVertex3f(x, -y, -z);
	glTexCoord2f(0, 0);
	glVertex3f(x, -y, z);
	glTexCoord2f(0, 1);
	glVertex3f(-x, -y, z);

	//top
	//glColor3f(1f,1f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, y, -z);
	glTexCoord2f(1, 0);
	glVertex3f(x, y, -z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(-x, y, z);
	glEnd();
	glPopMatrix();
}
void GFX::drawGrass(float x, float y, float z, float xx, float yy, float zz, Texture* texture, Texture* top, Texture* bottom){
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	//glLoadIdentity();
	glTranslatef(xx, yy, zz);
	glPushMatrix();
	glBegin(GL_QUADS);
	//Front face
	//glColor3f(1f,0f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1, 0);
	glVertex3f(-x, y, z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(x, -y, z);
	//Backface
	//glColor3f(0f,1f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1, 0);
	glVertex3f(-x, y, -z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, -z);
	glTexCoord2f(0, 1);
	glVertex3f(x, -y, -z);
	//left
	//glColor3f(0f,0f,1f);
	glTexCoord2f(0, 1);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, z);
	glTexCoord2f(1, 0);
	glVertex3f(-x, y, z);
	glTexCoord2f(0, 0);
	glVertex3f(-x, y, -z);
	//right
	//glColor3f(1f,0f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(x, -y, -z);
	glTexCoord2f(0, 1);
	glVertex3f(x, -y, z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(1, 0);
	glVertex3f(x, y, -z);

	//			//Bottom Face
	//			//glColor3f(.75f,.05f,.05f);
	//			glTexCoord2f(1,1);
	//			glVertex3f(-x,-y,-z);
	//			glTexCoord2f(1,0);
	//			glVertex3f(x,-y,-z);
	//			glTexCoord2f(0,0);
	//			glVertex3f(x,-y,z);
	//			glTexCoord2f(0,1);
	//			glVertex3f(-x,-y,z);

	//top

	//top.bind();
	//glColor3f(1f,1f,1f);
	//			glTexCoord2f(1,1);
	//			glVertex3f(-x,y,-z);
	//			glTexCoord2f(1,0);
	//			glVertex3f(x,y,-z);
	//			glTexCoord2f(0,0);
	//			glVertex3f(x,y,z);
	//			glTexCoord2f(0,1);
	//			glVertex3f(-x,y,z);
	glEnd();
	glPopMatrix();


	//glLoadIdentity();
	//glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, top.getTextureID());
	glBindTexture(GL_TEXTURE_2D, top->getTexture());
	glBegin(GL_QUADS);
	//glColor3f(1f,1f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(-x, y, -z);
	glTexCoord2f(1, 0);
	glVertex3f(x, y, -z);
	glTexCoord2f(0, 0);
	glVertex3f(x, y, z);
	glTexCoord2f(0, 1);
	glVertex3f(-x, y, z);
	glEnd();


	//Bottom Face
	//glColor3f(.75f,.05f,.05f);
	glBindTexture(GL_TEXTURE_2D, bottom->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-x, -y, -z);
	glTexCoord2f(1, 0);
	glVertex3f(x, -y, -z);
	glTexCoord2f(0, 0);
	glVertex3f(x, -y, z);
	glTexCoord2f(0, 1);
	glVertex3f(-x, -y, z);
	glEnd();
	//glPopMatrix();
	//glLoadIdentity();
}

void GFX::drawTestCube(float x, float y, float z, float xx, float yy, float zz, Texture* texture){
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	//glLoadIdentity();
	//glTranslatef(xx,yy,zz);
	glPushMatrix();
	glBegin(GL_QUADS);
	//Front face
	//glColor3f(1f,0f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(-x + xx, y + yy, z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(x + xx, -y + yy, z + zz);
	//Backface
	//glColor3f(0f,1f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, -z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(-x + xx, y + yy, -z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, -z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(x + xx, -y + yy, -z + zz);
	//left
	//glColor3f(0f,0f,1f);
	glTexCoord2f(0, 1);
	glVertex3f(-x + xx, -y + yy, -z + zz);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(-x + xx, y + yy, z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(-x + xx, y + yy, -z + zz);
	//right
	//glColor3f(1f,0f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(x + xx, -y + yy, -z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(x + xx, -y + yy, z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(x + xx, y + yy, -z + zz);

	//Bottom Face
	//glColor3f(.75f,.05f,.05f);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, -z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(x + xx, -y + yy, -z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, -y + yy, z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(-x + xx, -y + yy, z + zz);

	//top
	//glColor3f(1f,1f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, y + yy, -z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(x + xx, y + yy, -z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(-x + xx, y + yy, z + zz);
	glEnd();
	glPopMatrix();
}

void GFX::drawGrassTest(float x, float y, float z, float xx, float yy, float zz, Texture* texture, Texture* top, Texture* bottom){
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	//glLoadIdentity();
	//glTranslatef(xx,yy,zz);
	glPushMatrix();
	glBegin(GL_QUADS);
	//Front face
	//glColor3f(1f,0f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(-x + xx, y + yy, z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(x + xx, -y + yy, z + zz);
	//Backface
	//glColor3f(0f,1f,0f);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, -z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(-x + xx, y + yy, -z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, -z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(x + xx, -y + yy, -z + zz);
	//left
	//glColor3f(0f,0f,1f);
	glTexCoord2f(0, 1);
	glVertex3f(-x + xx, -y + yy, -z + zz);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(-x + xx, y + yy, z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(-x + xx, y + yy, -z + zz);
	//right
	//glColor3f(1f,0f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(x + xx, -y + yy, -z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(x + xx, -y + yy, z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(x + xx, y + yy, -z + zz);
	glEnd();
	glPopMatrix();


	//glLoadIdentity();
	//glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, top.getTextureID());
	glBindTexture(GL_TEXTURE_2D, top->getTexture());
	glBegin(GL_QUADS);
	//glColor3f(1f,1f,1f);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, y + yy, -z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(x + xx, y + yy, -z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, y + yy, z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(-x + xx, y + yy, z + zz);
	glEnd();


	//Bottom Face
	//glColor3f(.75f,.05f,.05f);
	glBindTexture(GL_TEXTURE_2D, bottom->getTexture());
	glBegin(GL_QUADS);
	glTexCoord2f(1, 1);
	glVertex3f(-x + xx, -y + yy, -z + zz);
	glTexCoord2f(1, 0);
	glVertex3f(x + xx, -y + yy, -z + zz);
	glTexCoord2f(0, 0);
	glVertex3f(x + xx, -y + yy, z + zz);
	glTexCoord2f(0, 1);
	glVertex3f(-x + xx, -y + yy, z + zz);
	glEnd();
	//glPopMatrix();
	//glLoadIdentity();
}

void GFX::drawCubeFromCorner(float xx, float yy, float zz, Texture* texture){
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	//glLoadIdentity();
	//glTranslatef(xx,yy,zz);
	glPushMatrix();
	glBegin(GL_QUADS);
	//Front Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy + 1, zz);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy + 1, zz);
	//Left Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy + 1, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy, zz + 1);
	glTexCoord2f(1, 1);
	glVertex3f(xx, yy, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx, yy + 1, zz);
	//Right Face
	glTexCoord2f(0, 0);
	glVertex3f(xx + 1, yy + 1, zz);
	glTexCoord2f(0, 1);
	glVertex3f(xx + 1, yy, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy, zz + 1);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy + 1, zz + 1);
	//Back Face
	glTexCoord2f(0, 0);
	glVertex3f(xx + 1, yy + 1, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx + 1, yy, zz + 1);
	glTexCoord2f(1, 1);
	glVertex3f(xx, yy, zz + 1);
	glTexCoord2f(1, 0);
	glVertex3f(xx, yy + 1, zz + 1);
	//Top Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy + 1, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy + 1, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy + 1, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy + 1, zz + 1);
	//Bottom Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy, zz + 1);
	glEnd();
	glPopMatrix();
}


void GFX::drawGrass(float xx, float yy, float zz, Texture* texture, Texture* top, Texture* bottom){
	glBindTexture(GL_TEXTURE_2D, texture->getTexture());
	//glLoadIdentity();
	//glTranslatef(xx,yy,zz);
	glPushMatrix();
	glBegin(GL_QUADS);
	//Front Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy + 1, zz);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy + 1, zz);
	//Back Face
	glTexCoord2f(0, 0);
	glVertex3f(xx + 1, yy + 1, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx + 1, yy, zz + 1);
	glTexCoord2f(1, 1);
	glVertex3f(xx, yy, zz + 1);
	glTexCoord2f(1, 0);
	glVertex3f(xx, yy + 1, zz + 1);
	//Left Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy + 1, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy, zz + 1);
	glTexCoord2f(1, 1);
	glVertex3f(xx, yy, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx, yy + 1, zz);
	//Right Face
	glTexCoord2f(0, 0);
	glVertex3f(xx + 1, yy + 1, zz);
	glTexCoord2f(0, 1);
	glVertex3f(xx + 1, yy, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy, zz + 1);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy + 1, zz + 1);
	glEnd();
	glPopMatrix();


	//glLoadIdentity();
	//glPushMatrix();
	//glBindTexture(GL_TEXTURE_2D, top.getTextureID());
	glBindTexture(GL_TEXTURE_2D, top->getTexture());
	glBegin(GL_QUADS);
	//Top Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy + 1, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy + 1, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy + 1, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy + 1, zz + 1);
	glEnd();


	//Bottom Face
	//glColor3f(.75f,.05f,.05f);
	glBindTexture(GL_TEXTURE_2D, bottom->getTexture());
	glBegin(GL_QUADS);
	//Bottom Face
	glTexCoord2f(0, 0);
	glVertex3f(xx, yy, zz + 1);
	glTexCoord2f(0, 1);
	glVertex3f(xx, yy, zz);
	glTexCoord2f(1, 1);
	glVertex3f(xx + 1, yy, zz);
	glTexCoord2f(1, 0);
	glVertex3f(xx + 1, yy, zz + 1);
	glEnd();
	//glPopMatrix();
	//glLoadIdentity();
	}