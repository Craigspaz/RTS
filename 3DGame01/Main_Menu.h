#pragma once
#include "Menu.h"
#include "Game.h"
#include "Button.h"
class Main_Menu :
	public Menu
{
public:
	Main_Menu(int width, int height, Input* input, int textureWidth, int textureHeight, Textures* textures);
	~Main_Menu();
	void update();
	void render();
private:
	int _width;
	int _height;
	Input* _input;
	int textureWidth;
	int textureHeight;
	Textures* _textures;

	Button* playButton;
	//Menu options
	bool hoverOverPlayButton_Main_Menu;
	bool hoverOverExitButton_Main_Menu;
};

