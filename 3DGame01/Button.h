#ifndef _BUTTON_H
#define _BUTTON_H
#include "RectangleBox.h"
#include "Texture.h"
#include "GFX.h"
#include "Input.h"
/*A button that will respond to different buttons being pressed by the mouse*/
class Button
{
public:
	Button(RectangleBox box, Texture* up,Texture* down, Texture* hover);
	void draw();
	void update(Input* input);
	void setBox(RectangleBox box);
	RectangleBox getBox();
	bool getIsUp();
	bool getIsHover();
	void setUp(bool a);
	void setHover(bool a);
	bool isButton1Clicked(Input* input);
	bool isButton2Clicked(Input* input);
	bool isButton3Clicked(Input* input);
	bool isButton4Clicked(Input* input);
	bool isButton5Clicked(Input* input);
	bool isButton6Clicked(Input* input);
	bool isButton7Clicked(Input* input);
	bool isButton8Clicked(Input* input);
	~Button();
private:
	RectangleBox _box;
	Texture* _up; //The texture for the button not being clicked
	Texture* _down; //The texture for the button being clicked
	Texture* _hover;
	bool isUp, isHover; // Is the button not being pressed and is the mouse hovering over the button
};

#endif