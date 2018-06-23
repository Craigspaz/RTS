#include "Main_Menu.h"


Main_Menu::Main_Menu(int width, int height, Input* input, int _textureWidth, int _textureHeight, Textures* textures) :
_width(width),
_height(height),
_input(input),
textureWidth(_textureWidth),
textureHeight(_textureHeight),
_textures(textures),
hoverOverExitButton_Main_Menu(false)
{
	RectangleBox playBox(newVector2f(_width / 2 - (textureWidth / 2), _height / 3 - (textureHeight / 2)),newVector2f(textureWidth,textureHeight));
	playButton = new Button(playBox, _textures->getPlayFirstTexture(), _textures->getPlaySecondTexture(), _textures->getPlaySecondTexture());
}

void Main_Menu::update()
{

	if (playButton->getBox().isOverlapping(RectangleBox(newVector2f(_input->getX(), _input->getY()), newVector2f(32, 32))))
	{
		hoverOverPlayButton_Main_Menu = true;
		if (_input->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
		{
			std::cout << "Play Button Pressed\n";
			hoverOverPlayButton_Main_Menu = false;
			hoverOverExitButton_Main_Menu = false;
			std::this_thread::sleep_for(std::chrono::seconds(1));
			Game::next = Game::GAME;
			Game::previous = Game::MAIN_MENU;
			Game::state = Game::LOADING;
		}
	}
	else
	{
		hoverOverPlayButton_Main_Menu = false;
	}
	//option button code
	//if (_input->getX() > _width / 2 - (textureWidth / 2) && _input->getX() < _width / 2 + (textureWidth / 2) && _input->getY() > _height / 3 + textureHeight && _input->getY() < _height / 3 + textureHeight + (textureHeight))
	//{
	//	hoverOverOptions_Menus = true;
	//	if (_input->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
	//	{
	//		std::cout << "OPTIONS Button Pressed\n";
	//		hoverOverPlayButton_Main_Menu = false;
	//		hoverOverExitButton_Main_Menu = false;
	//		hoverOverOptions_Menus = false;
	//		std::this_thread::sleep_for(std::chrono::seconds(1));
	//		Game::state = Game::OPTIONS;
	//		Game::previous = Game::MAIN_MENU;
	//	}
	//}
	//else
	//{
	//	hoverOverOptions_Menus = false;
	//}
	//exit button code
	if (_input->getX() > _width / 2 - (textureWidth / 2) && _input->getX() < _width / 2 + (textureWidth / 2) && _input->getY() > 2 * _height / 3 - (textureHeight / 2) && _input->getY() < 2 * _height / 3 + (textureHeight / 2))
	{
		hoverOverExitButton_Main_Menu = true;
		if (_input->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
		{
			std::cout << "Exit Button Pressed\n";
			hoverOverPlayButton_Main_Menu = false;
			hoverOverExitButton_Main_Menu = false;
			exit(0);
		}
	}
	else
	{
		hoverOverExitButton_Main_Menu = false;
	}
}

void Main_Menu::render()
{
	GFX::drawRect(_width, _height, 0, 0, _textures->getBackgroundTestTexture());
	playButton->draw();
	GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 + textureHeight, _textures->getOptionsFirstTexture());
	//if (hoverOverOptions_Menus)
	//{
	//	GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 + textureHeight, _textures->getOptionsSecondTexture());
	//}
	GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2), _textures->getExitFirstTexture());
	if (hoverOverExitButton_Main_Menu)
	{
		GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2), _textures->getExitSecondTexture());
	}
}


Main_Menu::~Main_Menu()
{
}
