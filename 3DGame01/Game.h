#ifndef _GAME_H
#define _GAME_H
/*This is the main class which handles updating and rendering the game*/
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <GLFW\glfw3.h>
#include "GFX.h"
#include "Textures.h"
#include "MenuTextures.h"
#include "Input.h"
#include <thread>
#include <chrono>
#include "Camera.h"
#include "Tile.h"
#include "Tank.h"
#include "Soldier.h"
#include <string>
#include <sstream>
#include "SystemDefs.h"
#include "Building.h"
#include "Builder.h"
#include "Sound.h"
#include "Button.h"
#include <CIMG\CImg.h>
#include "BiomeInfo.h"
#include "IslandListItem.h"
#include "BuildingItemsListItem.h"

class Game
{
public:
	Game(int width, int height);

	void update();
	void render();
	~Game();


	bool getVsync();
	bool getMSAA();

	bool cleanup();
	void loadWorld(); //Loads the world from a file


	void setWorld(Tile* world[][8192]); 
	
private:
	int _height;
	int _width;
	enum State { MAIN_MENU, GAME, OPTIONS, PAUSE_MENU,LOADING}; // Stores which menu you are in
	State state;
	State previous;
	State next;
	bool _hasGeneratedMiniMap;

	Textures* _textures; //Stores all of the textures
	MenuTextures* _menuTextures;
	Input* _input; // Handles all keyboard or mouse input
	Camera* _camera; // The game view and camera

	Sound* testSound; //This is a temp variable used for testing sound


	int textureWidth; //This is the width of the main menu items.
	int textureHeight;//This is the height of the main menu items.

	Vector2f mouseClicked; // Stores the position of a mouse click. Used to know where to draw selection box
	bool mouseSelectionClicked; //Stores if the user clicked and the position of the click is stored in variable above

	bool mouseDown; //helps fix issue when clicking registers as multiple clicks
	int mouseDownTimer;//helps fix issue when clicking registers as multiple clicks
	bool selectingSingleUnits; // Makes sure units are not being selecte
	
	Button* playButton;
	Button* exitButton;
	Button* optionsButton;
	Button* resumeButton;
	Button* optionsPauseMenu;
	Button* exitPauseMenu;
	//Options	TODO STORE SETTINGS IN FILE
	bool vsync;
	bool msaa;

	//TODO DIFFERENT GRAPHICS LEVELS
	enum TEXTUREQUALITY{LOW, MEDIUM, HIGH, ULTRA};
	TEXTUREQUALITY texQual;

	//TODO MUSIC OPTIONS
	bool musicEnabled;

	Tile* _tiles[8192][8192]; //Map arrary
	std::vector<Unit*>* _units; //Array of units
	std::vector<Building*>* _buildings; //Array of buildings
	std::vector<Unit*>* _selectedUnits; //Array of selected units
	std::vector<Tile*>* _tilesCheckInBridgeConnectionTesting;
	bool hasUnitsSelected;
	Tile* destinationTile;
	int mapWidth;
	int mapHeight;


	bool loaded; //Map is loaded
	bool loading; //Map is loading

	int selectedBuilderID; //ID of the builder unit selected
	std::vector<Builder*>* _builders; //Array of builders 
	Builder* selectedBuilder;// TEMP Player will handle later
	bool isBuilderSelected;// TEMP Player will handle later
	std::vector<IslandListItem>* _islandMap;
	bool _hasBuildingSelected; // TEMP Player will handle later
	Building* _selectedBuilding; // TEMP Player will handle later
	bool _hasBuildingListItemSelected;
	int _idOfBuildingItemHover;
	std::vector<BuildingItemsListItem*>* _testFactory1;

	bool hoverOverStop;//hover of stop button
	bool hoverOverABuildingInList; //temp hover of test building
	int idOfBuildingInList;

	bool isPlacingBuilding; 
	int PlacingBuildingID;

	Vector2f hoverPosition; //mouse position over world when placing a building
	Vector2f hoverBuildingSize; //size of building being placed

	bool canPlaceBuildingThere; //a boolean that keeps track if a building can be placed at the mouse location on map

	int playerStartingCash; //TODO: implement

	std::vector<Building*>* _listOfAllBuildings; //List of all possible buildable buildings to display on hud

	bool _destIsBuilding;
	Building* destBuilding;
	int currentBuildingID;
	std::vector<Texture*>* tankTextures = new std::vector<Texture*>();
	std::vector<Texture*>* soldierTextures = new std::vector<Texture*>();
	std::vector<Texture*>* builderTextures = new std::vector<Texture*>();

};

#endif