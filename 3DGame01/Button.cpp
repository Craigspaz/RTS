#include "Button.h"


Button::Button(RectangleBox box, Texture* up, Texture* down, Texture* hover):
_box(box),
_up(up),
_down(down),
_hover(hover),
isUp(true),
isHover(false)
{
}

void Button::draw()
{
	if (isUp)
	{
		GFX::drawRect(_box.getSize().x, _box.getSize().y, _box.getPosition().x, _box.getPosition().y, _up);
	}
	else
	{
		GFX::drawRect(_box.getSize().x, _box.getSize().y, _box.getPosition().x, _box.getPosition().y, _down);
	}
	if (isHover)
	{
		GFX::drawRect(_box.getSize().x, _box.getSize().y, _box.getPosition().x, _box.getPosition().y, _hover);
	}
}

bool Button::getIsUp()
{
	return isUp;
}

bool Button::getIsHover()
{
	return isHover;
}


void Button::setUp(bool a)
{
	isUp = a;
}
void Button::setHover(bool a)
{
	isHover = a;
}

void Button::update(Input* input)
{
	if (RectangleBox(newVector2f(input->getX(), input->getY()), newVector2f(32, 32)).isOverlapping(getBox()))
	{
		isHover = true;
	}
	else
	{
		isHover = false;
	}
}

void Button::setBox(RectangleBox box)
{
	_box = box;
}

RectangleBox Button::getBox()
{
	return _box;
}

Button::~Button()
{

}


bool Button::isButton1Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_1))
	{
		return true;
	}
	return false;
}
bool Button::isButton2Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_2))
	{
		return true;
	}
	return false;
}

bool Button::isButton3Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_3))
	{
		return true;
	}
	return false;
}
bool Button::isButton4Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_4))
	{
		return true;
	}
	return false;
}
bool Button::isButton5Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_5))
	{
		return true;
	}
	return false;
}
bool Button::isButton6Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_6))
	{
		return true;
	}
	return false;
}
bool Button::isButton7Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_7))
	{
		return true;
	}
	return false;
}
bool Button::isButton8Clicked(Input* input)
{
	if (isHover && input->getMouseState(GLFW_MOUSE_BUTTON_8))
	{
		return true;
	}
	return false;
}
