#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <string>
#include <cstring>
#include "Game.h"
#include <SOIL.h>
#include <thread>
#include <chrono>
//The include below is commented out until I get to adding Audio
//#include <SFML\Audio.hpp>

//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup") //Uncomment to block CMD from launching. Use for a release build

int main(int argc, char** argv)
{
	//TODO: add commandline arguments

	//Basic Audio Example Code
	//sf::SoundBuffer soundBuffer;
	//sf::Sound sound;
	//if (!soundBuffer.loadFromFile("./res/audio/Adventure_Meme.wav"))
	//{
	//	std::cout << "Can't find sound\n";
	//}
	//sound.setBuffer(soundBuffer);
	//sound.play();

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	//Load Width and Height from a txt file
	int width = 1366;
	int height = 768;
	std::ifstream file("settings.txt");
	if (file.is_open())
	{
		std::string line;
		int l = 0;
		while (std::getline(file, line))
		{
			if (l == 0)
			{
				width = std::stoi(line);
			}
			if (l == 1)
			{
				height = std::stoi(line);
			}
			l++;
		}
	}
	file.close();

	//Write the version of the game to a text file so then an updater program can check the current version
	const std::string VERSION = "1.6.3";
	std::ofstream ver;
	ver.open("version.txt");
	ver << VERSION << std::endl;
	ver.close();
	
	const std::string TITLE = ("RTS " + VERSION);

	//Gets the primary monitor
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	int monitorCount;
	GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
	std::cout << "There are : " << monitorCount << " monitors.\n";

	//fullscreen settings
	const GLFWvidmode* mode = glfwGetVideoMode(primary);
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
	glfwWindowHint(GLFW_ALPHA_BITS, 8);
	glfwWindowHint(GLFW_SAMPLES, (8 + mode->redBits + mode->greenBits + mode->blueBits));
	GLFWwindow* window = glfwCreateWindow(width, height, TITLE.c_str(), primary, NULL); //Good for full screen release build
	//GLFWwindow* window = glfwCreateWindow(width, height, TITLE.c_str(), NULL, NULL); //Good for windowed mode
	//Development Window below
	//GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, TITLE.c_str(), NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glewInit();
	//Calculate timing for update rate
	double lastTime = glfwGetTime();
	double deltaTime = 0.0f;
	//sets cursor image
	GLFWimage image;
	int w, h;
	int channels;
	unsigned char* p = new unsigned char[16 * 16 * 4];
	memset(p, 0xff, sizeof(p));
	p = SOIL_load_image("res/cursor.dds", &w, &h, &channels, SOIL_LOAD_RGBA);
	image.width = w;
	image.height = h;
	image.pixels = p;
	GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
	glfwSetCursor(window, cursor);

	//Update Rate
#define Updates_Per_Second 60.0f

	//Configure OPENGL matrix configuration
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Objects
	Game* game = new Game(width, height);

	bool msaa = false;
	//Main game loop
	while (!glfwWindowShouldClose(window))
	{
		//MSAA - Note- May not be working
		if (game->getMSAA())
		{
			glEnable(GL_MULTISAMPLE_ARB);
			msaa = true;
		}
		else
		{
			if (msaa == true)
			{
				glDisable(GL_MULTISAMPLE_ARB);
			}
			msaa = false;
		}
		//Viewport
		float ratio;
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);
		ratio = w / (float)h;
		glViewport(0, 0, w, h);

		// Updates the update timer
		double currentTime = glfwGetTime();
		deltaTime += (currentTime - lastTime) * Updates_Per_Second;
		lastTime = currentTime;

		//Clears buffers
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		while (deltaTime >= 1.0f / Updates_Per_Second)
		{
			//update the game
			game->update();
			--deltaTime;
		}
		//render
		game->render();
		glfwSwapBuffers(window);
		//Vsyc Settings. Note - Will sync to 60 fps
		if (game->getVsync())
		{
			glfwSwapInterval(60);
		}
		glfwPollEvents();
	}
	SOIL_free_image_data(p); // Frees memory SOIL used
	glfwDestroyCursor(cursor); // Frees the memory the cursor is using
	glfwDestroyWindow(window); // Frees the memory the window is using
	glfwTerminate(); // Frees the memory glfw is using
	//system("PAUSE"); //Just if you want to pause console at end
	return 0;
}

