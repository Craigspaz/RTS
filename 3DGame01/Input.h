#ifndef INPUT_H
#define INPUT_H
/*This handles all of the mouse and the keyboard input*/
#include <iostream>
#include <GLFW\glfw3.h>
#include "RectangleBox.h"
class Input
{
private:
	Input();
	~Input();
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool KEYS[348];
	void cursor_position_callback(GLFWwindow* window, double x, double y);
	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	void scroll_callback(GLFWwindow* window, double x, double y);
	double _x;
	double _y;
	GLFWimage* image;
	bool MOUSE[12];
	RectangleBox* _box;
public:
	static Input& getInput();
	static void destroyInput();
	static void keyCallbackFun(GLFWwindow* window, int key, int scancode, int action, int mods);
	bool getKeyState(int key);
	double getX();
	double getY();
	bool getMouseState(int button);
	static void cursor_position_callbackFun(GLFWwindow* window, double x, double y);
	static void mouse_button_callbackFun(GLFWwindow* window, int button, int action, int mods);
	static void scroll_callbackFun(GLFWwindow* window, double x, double y);
};

#endif