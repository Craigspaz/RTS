#include "Input.h"


Input::Input()
	: _x(0), _y(0)
{
	for (int i = 0; i < 348; i++)
	{
		KEYS[i] = false;
	}
	for (int i = 0; i < 12; i++)
	{
		MOUSE[i] = false;
	}
	_box = new RectangleBox(newVector2f(_x, _y), newVector2f(32, 32));
}




Input::~Input()
{
}

double Input::getX()
{
	return _x;
}
double Input::getY()
{
	return _y;
}

void Input::cursor_position_callbackFun(GLFWwindow* window, double x, double y)
{
	Input* mouse = &getInput();
	mouse->cursor_position_callback(window, x, y);
}


void Input::cursor_position_callback(GLFWwindow* window, double x, double y)
{
	_x = x;
	_y = y;
}

void Input::scroll_callback(GLFWwindow* window, double x, double y)
{

}

void Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		MOUSE[button] = true;
		//std::cout << "MOUSE Button Pressed\n";
	}
	else
	{
		MOUSE[button] = false;
		//std::cout << "MOUSE Button RELEASED\n";
	}
}


void Input::mouse_button_callbackFun(GLFWwindow* window, int button, int action, int mods)
{
	Input* mouse = &getInput();
	mouse->mouse_button_callback(window, button, action, mods);
}

bool Input::getMouseState(int button)
{
	return MOUSE[button];
}

void Input::scroll_callbackFun(GLFWwindow* window, double x, double y)
{
	Input* mouse = &getInput();
	mouse->scroll_callback(window, x, y);
}


void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
	//	if (GLFW_CURSOR_DISABLED == glfwGetInputMode(glfwGetCurrentContext(), GLFW_CURSOR))
	//	{
	//		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//	}
	//	else
	//	{
	//		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//	}
	//}
	if (action == GLFW_PRESS)
	{
		KEYS[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		KEYS[key] = false;
	}
	else
	{
		KEYS[key] = true;
	}
}

void Input::keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Input* keyboard = &getInput();
	keyboard->keyCallback(window, key, scancode, action, mods);
}

Input& Input::getInput()
{
	static Input* keyboard = NULL;
	if (keyboard == NULL)
	{
		glfwSetKeyCallback(glfwGetCurrentContext(), *keyCallbackFun);
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		glfwSetCursorPosCallback(glfwGetCurrentContext(), *cursor_position_callbackFun);
		glfwSetMouseButtonCallback(glfwGetCurrentContext(), *mouse_button_callbackFun);
		glfwSetScrollCallback(glfwGetCurrentContext(), *scroll_callbackFun);
		glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		keyboard = new Input();
	}
	return *keyboard;
}

void Input::destroyInput()
{
	Input* keyboard = &getInput();
	delete keyboard;
}

bool Input::getKeyState(int key)
{
	return KEYS[key];
}
