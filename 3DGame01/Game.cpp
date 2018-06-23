#include "Game.h"


Game::Game(int width, int height) :
//Initializes alot of variables
_width(width),
_height(height),
state(MAIN_MENU),
previous(MAIN_MENU),
next(MAIN_MENU),
_input(&Input::getInput()),
vsync(false),
msaa(false),
musicEnabled(false),
texQual(LOW),
mouseClicked(newVector2f(0, 0)),
mouseSelectionClicked(false),
mouseDown(false),
hasUnitsSelected(false),
loaded(false),
loading(false),
selectedBuilderID(-1),
isBuilderSelected(false),
hoverOverStop(false),
hoverOverABuildingInList(false),
isPlacingBuilding(false),
canPlaceBuildingThere(true),
idOfBuildingInList(0),
mouseDownTimer(0),
_destIsBuilding(false),
currentBuildingID(0),
_hasGeneratedMiniMap(false),
_hasBuildingSelected(false),
_hasBuildingListItemSelected(false)
{
	//Calculates the texture width and height based on the width of the screen
	if (width >= 2880) //by 1620
	{
		textureWidth = 1024;
		textureHeight = 256;
		TEXTUREWIDTH = 128;
		TEXTUREHEIGHT = 128;
	}
	else if (width > 1920)
	{
		textureWidth = 512;
		textureHeight = 128;
		TEXTUREWIDTH = 64;
		TEXTUREWIDTH = 64;
	}
	else if (width == 1920)
	{
		textureWidth = 512;
		textureHeight = 128;
		TEXTUREWIDTH = 32;
		TEXTUREHEIGHT = 32;
	}
	else if (width >= 1366)
	{
		textureWidth = 256;
		textureHeight = 128;
		TEXTUREWIDTH = 32;
		TEXTUREHEIGHT = 32;
	}
	else if (width >= 800)
	{
		textureWidth = 128;
		textureHeight = 64;
		TEXTUREWIDTH = 16;
		TEXTUREHEIGHT = 16;
	}
	_menuTextures = new MenuTextures(); //Initializes Menu Textures
	_islandMap = new std::vector<IslandListItem>();
	_camera = new Camera(newVector2f(0, 0), newVector2f(width, height), 0); // initializes the camera
	_units = new std::vector<Unit*>(); // this is a list of all of the units on the world
	_buildings = new std::vector<Building*>(); //this is a list of all of the buildings on the map
	_selectedUnits = new std::vector<Unit*>(); //this is a list of all of the units selected
	_builders = new std::vector<Builder*>(); //this is a list of all of the builders in a world. TODO make player based lists
	_tilesCheckInBridgeConnectionTesting = new std::vector<Tile*>();
	testSound = new Sound("./res/audio/Adventure_Meme.wav"); //Temp just to create a new sound for testing music

	
	//Creates menu buttons
	std::cout << "Width : " << _width << std::endl;
	playButton = new Button(RectangleBox(newVector2f(_width / 2 - (textureWidth / 2), _height / 3 - (textureHeight / 2)), newVector2f(textureWidth, textureHeight)), _menuTextures->getPlayFirstTexture(), _menuTextures->getPlaySecondTexture(), _menuTextures->getPlaySecondTexture());
	optionsButton = new Button(RectangleBox(newVector2f(_width / 2 - (textureWidth / 2), _height / 3 + textureHeight), newVector2f(textureWidth, textureHeight)), _menuTextures->getOptionsFirstTexture(), _menuTextures->getOptionsSecondTexture(), _menuTextures->getOptionsSecondTexture());
	exitButton = new Button(RectangleBox(newVector2f(_width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2)), newVector2f(textureWidth, textureHeight)), _menuTextures->getExitFirstTexture(), _menuTextures->getExitSecondTexture(), _menuTextures->getExitSecondTexture());

	resumeButton = new Button(RectangleBox(newVector2f(_width / 2 - (textureWidth / 2), _height / 3 - (textureHeight / 2)), newVector2f(textureWidth, textureHeight)), _menuTextures->getResumeFirstTexture(), _menuTextures->getResumeSecondTexture(), _menuTextures->getResumeSecondTexture());
	optionsPauseMenu = new Button(RectangleBox(newVector2f(_width / 2 - (textureWidth / 2), _height / 3 + textureHeight), newVector2f(textureWidth, textureHeight)), _menuTextures->getOptionsFirstTexture(), _menuTextures->getOptionsSecondTexture(), _menuTextures->getOptionsSecondTexture());
	exitPauseMenu = new Button(RectangleBox(newVector2f(_width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2)), newVector2f(textureWidth, textureHeight)), _menuTextures->getExitFirstTexture(), _menuTextures->getExitSecondTexture(), _menuTextures->getExitSecondTexture());
	std::cout << "Generating World... Please Wait...\n";
}



bool Game::getVsync()
{
	return vsync; // used to give information to main function
}

bool Game::getMSAA()
{
	return msaa;// used to give information to main function
}


bool check(std::vector<Vector2f>* list, Vector2f t)
{
	for (std::vector<Vector2f>::iterator i = list->begin(); i < list->end(); i++)
	{
		if ((*i).x = t.x && (*i).y == t.y)
		{
			return true;
		}
	}
	return false;
}

bool check(std::vector<std::string>* list, std::string t)
{
	for (std::vector<std::string>::iterator i = list->begin(); i < list->end(); i++)
	{
		if ((*i) == t)
		{
			return true;
		}
	}
	return false;
}

void Game::update()
{
	//Music
	//if (testSound->isPlaying() == false)
	//{
	//	testSound->play();
	//	std::cout << "Calling Play...\n";
	//}
	//if (_input->getKeyState(GLFW_KEY_6))
	//{
	//	testSound->pause();
	//}
	if (state == MAIN_MENU)// executes if at the main menu
	{
		playButton->update(_input);
		optionsButton->update(_input);
		exitButton->update(_input);
		//Play button code
		if (playButton->isButton1Clicked(_input))
		{
			std::cout << "Play Button Pressed\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			next = GAME;
			previous = MAIN_MENU;
			state = LOADING;
		}
		//option button code
		if (optionsButton->isButton1Clicked(_input))
		{
			std::cout << "OPTIONS Button Pressed\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			state = OPTIONS;
			previous = MAIN_MENU;
		}
		
		//exit button code
		
		if (exitButton->isButton1Clicked(_input))
		{
			std::cout << "Exit Button Pressed\n";
			exit(0);
		}
	}
	else if (state == GAME)// if playing the game part of the game
	{
		if (_hasGeneratedMiniMap == false)
		{ 
			_textures = new Textures();
			_hasGeneratedMiniMap = true;

			//TEMP
			//creates 3 units one a tank, a soldier, and a builder
			tankTextures->push_back(_textures->getTankUpTexture());
			tankTextures->push_back(_textures->getTankDownTexture());
			tankTextures->push_back(_textures->getTankLeftTexture());
			tankTextures->push_back(_textures->getTankRightTexture());
			tankTextures->push_back(_textures->getTankUpLeftTexture());
			tankTextures->push_back(_textures->getTankUpRightTexture());
			tankTextures->push_back(_textures->getTankDownRightTexture());
			tankTextures->push_back(_textures->getTankDownLeftTexture());
			soldierTextures->push_back(_textures->getSoldierUpTexture());
			soldierTextures->push_back(_textures->getSoldierDownTexture());
			soldierTextures->push_back(_textures->getSoldierLeftTexture());
			soldierTextures->push_back(_textures->getSoldierRightTexture());
			soldierTextures->push_back(_textures->getSoldierLeftTexture());
			soldierTextures->push_back(_textures->getSoldierRightTexture());
			soldierTextures->push_back(_textures->getSoldierRightTexture());
			soldierTextures->push_back(_textures->getSoldierLeftTexture());

			builderTextures->push_back(_textures->getPlayerBackTexture());
			builderTextures->push_back(_textures->getPlayerFrontTexture());
			builderTextures->push_back(_textures->getPlayerLeftTexture());
			builderTextures->push_back(_textures->getPlayerRightTexture());
			builderTextures->push_back(_textures->getPlayerLeftTexture());
			builderTextures->push_back(_textures->getPlayerRightTexture());
			builderTextures->push_back(_textures->getPlayerRightTexture());
			builderTextures->push_back(_textures->getPlayerLeftTexture());


			int idCounter = 0;

			_units->push_back(new Tank(idCounter, "Tank", newVector2f(32, 32), tankTextures, 10, 50, DEFAULT_RANK, 0.5f, true, FACTION1,0));
			idCounter++;
			_units->push_back(new Soldier(idCounter, "Soldier", newVector2f(64, 64), soldierTextures, 10, 20, DEFAULT_RANK, 0.5f, true, FACTION2,0));
			idCounter++;
			_units->push_back(new Builder(idCounter, "Builder", newVector2f(32, 64), builderTextures, 0, 100, DEFAULT_RANK, 0.5f, true, FACTION1,0));
			_builders->push_back(new Builder(idCounter, "Builder", newVector2f(32, 64), builderTextures, 0, 100, DEFAULT_RANK, 0.5f, true, FACTION1,0));
			idCounter++;


			//Creates a static builder
			_buildings->push_back(new Building(newVector2f(TEXTUREWIDTH * 8, 128), newVector2f(64, 64), "Factory", 6, _textures->getBuildingFactoryTexture(), -1, NEUTRAL_FACTION));

			playerStartingCash = 5000;

			//adds buildings to the master list of buildings
			_listOfAllBuildings = new std::vector<Building*>();
			_listOfAllBuildings->push_back(new Building(newVector2f(0, 0), newVector2f(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2), "Factory", TEST_BUIDING_ID, _textures->getBuildingFactoryTexture(), currentBuildingID++, FACTION1));
			_listOfAllBuildings->push_back(new Building(newVector2f(0, 0), newVector2f(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2), "Barracks", TEST_BUIDING_BARRACKS_ID, _textures->getBuildingBarracksTexture(), currentBuildingID++, FACTION2));
			_listOfAllBuildings->push_back(new Building(newVector2f(0, 0), newVector2f(TEXTUREWIDTH, TEXTUREHEIGHT), "Bridge", BRIDGE_ID, _textures->getBridgeTexture(), currentBuildingID++, NEUTRAL_FACTION));

			hoverBuildingSize = newVector2f(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2);// initializes the size of the buildings

			_testFactory1 = new std::vector<BuildingItemsListItem*>();
			_testFactory1->push_back(new BuildingItemsListItem("Soldier", "Ground Human Unit", 0, _textures->getSoldierDownTexture(),0.01f,SOLDIER_TYPE));
			_testFactory1->push_back(new BuildingItemsListItem("Builder", "Builds Buildings", 0, _textures->getPlayerFrontTexture(),0.01f,BUILDER_TYPE));


			//END TEMP
		}
		//pause game controls
		if (_input->getKeyState(GLFW_KEY_ESCAPE))
		{
			state = PAUSE_MENU;
			previous = GAME;
			std::cout << "Open Pause Menu\n";
		}
		//camera movement with keyboard. May be temp
		if (_input->getX() <= 0 || _input->getKeyState(GLFW_KEY_LEFT))
		{
			_camera->moveRight();
		}
		if (_input->getX() >= _width-1 || _input->getKeyState(GLFW_KEY_RIGHT))
		{
			_camera->moveLeft();
		}
		if (_input->getY() <= 0 || _input->getKeyState(GLFW_KEY_UP))
		{
			_camera->moveUp();
		}
		if (_input->getY() >= _height-1 || _input->getKeyState(GLFW_KEY_DOWN))
		{
			_camera->moveDown();
		}
		//cleans up the camera view for calculations later
		int tempx = _width - mapWidth - 10;
		int tempy = (2 * _height / 3) + 25; 
		if (_input->getX() > tempx && _input->getX() < tempx + mapWidth && _input->getY() > tempy && _input->getY() < tempy + mapHeight && _input->getMouseState(GLFW_MOUSE_BUTTON_1))
		{
			int xtoSet = (_input->getX() - tempx - ((_width / TEXTUREWIDTH / 2))) * TEXTUREWIDTH - TEXTUREWIDTH;
			int ytoSet = (_input->getY() - tempy) * TEXTUREHEIGHT - TEXTUREHEIGHT;
			_camera->setPosition(newVector2f(-xtoSet, -ytoSet));
		}

		int camerax = -_camera->getPosition().x;
		int cameray = -_camera->getPosition().y;
		int cameramx = (-_camera->getPosition().x) + _width;
		int cameramy = (-_camera->getPosition().y) + (2 * _height / 3);

		int mousex = camerax + _input->getX();
		int mousey = cameray + _input->getY();	
		//Checks if the user is placing a building
		if (_hasBuildingSelected)
		{
			for (int j = 0; j < _testFactory1->size();j++)
			{
				if (_input->getX() >= (TEXTUREWIDTH * 10 + ((2 * j) * TEXTUREWIDTH)) && _input->getX() <= (TEXTUREWIDTH * 10 + ((2 * j) * TEXTUREWIDTH)) + TEXTUREWIDTH * 2 && _input->getY() > (2 * _height / 3) + 25 && _input->getY() < (2 * _height / 3) + 25 + TEXTUREWIDTH * 2)
				{
					if (_input->getMouseState(GLFW_MOUSE_BUTTON_1))
					{
						for (std::vector<Building*>::iterator i = _buildings->begin(); i != _buildings->end(); i++)
						{
							if ((*i)->getId() == _selectedBuilding->getId())
							{
								if (_testFactory1->at(j)->getItemType() == SOLDIER_TYPE)
								{
									(*i)->addToQueue(new Soldier(-1, _testFactory1->at(j)->getName(), (*i)->getPosition(), soldierTextures, 10, 100, DEFAULT_RANK, 0.5f, true, FACTION1,_testFactory1->at(j)->getSpeedToBuild()));
								}
								break;
							}
						}
					}
					_hasBuildingListItemSelected = true;
					_idOfBuildingItemHover = j;
					break;
				}
				else{
					_hasBuildingListItemSelected = false;
				}
			}
		}else if (isPlacingBuilding)
		{
			_hasBuildingListItemSelected = false;
			hoverPosition.x = mousex;
			hoverPosition.y = mousey;
			int startx = hoverPosition.x;
			int starty = hoverPosition.y;
			int endx = hoverPosition.x + hoverBuildingSize.x;
			int endy = hoverPosition.y + hoverBuildingSize.y;
			bool d = false;
			canPlaceBuildingThere = true;
			//checks for buildings in the way of placing a building
			for (int x = startx; x < endx; x++)
			{
				for (int y = starty; y < endy; y++)
				{
					if (_tiles[(int)(x/TEXTUREWIDTH)][(int)(y/TEXTUREHEIGHT)]->getTravelable() == false)
					{
						canPlaceBuildingThere = false;
						d = true;
						break;
					}
				}
				if (d == true)
				{
					break;
				}
			}
			if (canPlaceBuildingThere)
			{
				//if there is no building then it checks for units in the way
				for (std::vector<Unit*>::iterator i = _units->begin(); i != _units->end(); i++)
				{
					int unitx = (*i)->getPosition().x;
					int unity = (*i)->getPosition().y;
					if (unitx > startx && unitx < endx && unity > starty && unity < endy)
					{
						canPlaceBuildingThere = false;
						break;
					}
					else if (unitx + TEXTUREWIDTH > startx && unitx + TEXTUREWIDTH < endx && unity > starty && unity < endy)
					{
						canPlaceBuildingThere = false;
						break;
					}
					else if (unitx > startx && unitx < endx && unity + TEXTUREHEIGHT > starty && unity + TEXTUREWIDTH < endy)
					{
						canPlaceBuildingThere = false;
						break;
					}
					else if (unitx + TEXTUREWIDTH > startx && unitx + TEXTUREWIDTH < endx && unity + TEXTUREHEIGHT > starty && unity + TEXTUREHEIGHT < endy)
					{
						canPlaceBuildingThere = false;
						break;
					}
				}
			}
		}

		if (isPlacingBuilding && PlacingBuildingID == BRIDGE_ID && _input->getMouseState(GLFW_MOUSE_BUTTON_1) && _input->getY() < (2 * _height / 3) && !_hasBuildingSelected)
		{
			RectangleBox* hoverBox = new RectangleBox(newVector2f((int)hoverPosition.x / TEXTUREWIDTH,(int)hoverPosition.y / TEXTUREHEIGHT), newVector2f(TEXTUREWIDTH,TEXTUREHEIGHT));
			std::cout << "Placing Bridge at position: " << hoverBox->getPosition().x << " Y: " << hoverBox->getPosition().y << " On tile type: " << _tiles[(int)hoverBox->getPosition().x][(int)hoverBox->getPosition().y]->getType();
			bool cont = true;
			if (_tiles[(int)hoverBox->getPosition().x][(int)hoverBox->getPosition().y]->getTravelable() == true)
			{
				cont = false;
				canPlaceBuildingThere = true;
			}
			for (std::vector<Building*>::iterator i = _buildings->begin(); i != _buildings->end(); i++)
			{
				RectangleBox* buildingBox = new RectangleBox((*i)->getPosition(), (*i)->getSize());
				if (hoverBox->isOverlapping(*buildingBox))
				{
					cont = false;
					canPlaceBuildingThere = false;
					break;
				}
				delete buildingBox;
			}
			delete hoverBox;
			if (cont)
			{
				std::cout << "Placing Bridge at position: " << hoverBox->getPosition().x << " Y: " << hoverBox->getPosition().y << " On tile type: " << _tiles[(int)hoverBox->getPosition().x][(int)hoverBox->getPosition().y]->getType();
				_buildings->push_back(new Building(newVector2f((int)((hoverPosition.x / TEXTUREWIDTH)) * TEXTUREWIDTH, (int)((hoverPosition.y / TEXTUREHEIGHT)) * TEXTUREHEIGHT), hoverBuildingSize, "Bridge", PlacingBuildingID, _textures->getBridgeTexture(), currentBuildingID++,NEUTRAL_FACTION));
				isPlacingBuilding = false;
				_hasBuildingListItemSelected = false;
				//TODO fix pathfinding code to accomidate destination being a building
				//temp
				for (std::vector<Building*>::iterator i = _buildings->begin(); i != _buildings->end(); i++)
				{
					Vector2f p = (*i)->getPosition();
					Vector2f s = (*i)->getSize();
					for (int x = (p.x) / TEXTUREWIDTH; x < (p.x + s.x) / TEXTUREWIDTH; x++)
					{
						for (int y = (p.y) / TEXTUREHEIGHT; y < (p.y + s.y) / TEXTUREHEIGHT; y++)
						{
							if ((*i)->getType() == BRIDGE_ID)
							{
								_tiles[x][y]->changeToBridge(_textures->getBridgeTexture());
							}
							else
							{
								_tiles[x][y]->setTravelable(false);
							}
						}
					}
				}
				//end temp
				for (std::vector<Unit*>::iterator a = _units->begin(); a != _units->end(); a++)
				{
					std::cout << "Selected Builder ID is " << selectedBuilderID << std::endl;
					if ((*a)->getID() == selectedBuilder->getID())
					{
						for (std::vector<Builder*>::iterator b = _builders->begin(); b != _builders->end(); b++)
						{
							if ((*b)->getID() == selectedBuilder->getID())
							{
								(*b)->setPosition((*a)->getPosition());
								(*b)->setDamage((*a)->getDamage());
								(*b)->setDestination((*a)->getDestination());
								(*b)->setDisplayTexture((*b)->getDisplayTexture());
								(*b)->setHealth((*b)->getHealth());
								(*b)->setID((*a)->getID());
								(*b)->setMoving((*a)->getMoving());
								//(*b)->setName((*a)->getName());
								(*b)->setOnGround((*a)->getOnGround());
								(*b)->setRank((*a)->getRank());
								(*b)->setSelected((*a)->getSelected());
								(*b)->setSpeed((*a)->getSpeed());
								(*b)->setWait((*a)->getWait());


								if (_destIsBuilding)
								{
									for (std::vector<Building*>::iterator c = _buildings->begin(); c != _buildings->end(); c++)
									{
										if ((*c)->getId() == destBuilding->getId())
										{
											(*b)->setBuilding((*c));
											_destIsBuilding = false;
										}
									}
								}
								else
								{
									(*b)->setBuilding(_buildings->at(_buildings->size() - 1));
								}
								(*b)->setIsBuilding(true);
								(*a) = (*b);
								break;
							}
						}
						Unit::findPath((*a), _tiles, _tiles[(int)(hoverPosition.x / TEXTUREWIDTH)][(int)(hoverPosition.y / TEXTUREHEIGHT)], mapWidth, mapHeight, true, _islandMap);

						break;
					}
				}
			}
		}
		else if (canPlaceBuildingThere && isPlacingBuilding && _input->getMouseState(GLFW_MOUSE_BUTTON_1) && _input->getY() < (2 * _height / 3) && !_hasBuildingSelected)
		{
			_hasBuildingListItemSelected = false;
			hoverOverABuildingInList = false;
			std::cout << "Clicked building\n";
			if (PlacingBuildingID == TEST_BUIDING_ID)
			{
				_buildings->push_back(new Building(hoverPosition, hoverBuildingSize, "Test Building", PlacingBuildingID, _textures->getBuildingFactoryTexture(),currentBuildingID++,FACTION1)); //TEMP FACTION!
				isPlacingBuilding = false;
			}
			else if (PlacingBuildingID == TEST_BUIDING_BARRACKS_ID)
			{
				_buildings->push_back(new Building(hoverPosition, hoverBuildingSize, "Test Barracks Building", PlacingBuildingID, _textures->getBuildingBarracksTexture(), currentBuildingID++, FACTION1)); // TEMP FACTION1
				isPlacingBuilding = false;
			}
			
			for (std::vector<Unit*>::iterator a = _units->begin(); a != _units->end(); a++)
			{
				std::cout << "Selected Builder ID is " << selectedBuilderID << std::endl;
				if ((*a)->getID() == selectedBuilder->getID())
				{
					for (std::vector<Builder*>::iterator b = _builders->begin(); b != _builders->end(); b++)
					{
						if ((*b)->getID() == selectedBuilder->getID())
						{
							(*b)->setPosition((*a)->getPosition());
							(*b)->setDamage((*a)->getDamage());
							(*b)->setDestination((*a)->getDestination());
							(*b)->setDisplayTexture((*b)->getDisplayTexture());
							(*b)->setHealth((*b)->getHealth());
							(*b)->setID((*a)->getID());
							(*b)->setMoving((*a)->getMoving());
							//(*b)->setName((*a)->getName());
							(*b)->setOnGround((*a)->getOnGround());
							(*b)->setRank((*a)->getRank());
							(*b)->setSelected((*a)->getSelected());
							(*b)->setSpeed((*a)->getSpeed());
							(*b)->setWait((*a)->getWait());


							if (_destIsBuilding)
							{
								for (std::vector<Building*>::iterator c = _buildings->begin(); c != _buildings->end(); c++)
								{
									if ((*c)->getId() == destBuilding->getId())
									{
										(*b)->setBuilding((*c));
										_destIsBuilding = false;
									}
								}
							}
							else
							{
								(*b)->setBuilding(_buildings->at(_buildings->size() - 1));
							}
							(*b)->setIsBuilding(true);
							(*a) = (*b);
							break;
						}
					}
					Unit::findPath((*a), _tiles, _tiles[(int)(hoverPosition.x / TEXTUREWIDTH)][(int)(hoverPosition.y / TEXTUREHEIGHT)], mapWidth, mapHeight, true,_islandMap);

					break;
				}
			}
		}

		//this stops the building placement process if user does not want to place a building
		if (isPlacingBuilding && _input->getMouseState(GLFW_MOUSE_BUTTON_2))
		{
			_hasBuildingListItemSelected = false;
			hoverOverABuildingInList = false;
			isPlacingBuilding = false;
		}

		//checks if units are selected
		if (hasUnitsSelected)
		{
			if (isBuilderSelected)// checks if the unit selected is a builder
			{
				if (!selectedBuilder->getIsBuiding())// checks if the builder is buiding
				{
					int size = _listOfAllBuildings->size();
					//checks if the user is clicking one of the buildings to build
					for (int j = 0; j < _listOfAllBuildings->size();j++)
					{
						if (_input->getX() >= (TEXTUREWIDTH * 10 + ((2 * j) * TEXTUREWIDTH)) && _input->getX() <= (TEXTUREWIDTH * 10 + ((2 * j) * TEXTUREWIDTH)) + TEXTUREWIDTH * 2 && _input->getY() > (2 * _height / 3) + 25 && _input->getY() < (2 * _height / 3) + 25 + TEXTUREWIDTH * 2)
						{
							hoverOverABuildingInList = true;
							idOfBuildingInList = j;
							//std::cout << "ID of Building in list " << idOfBuildingInList << std::endl;
							if (_input->getMouseState(GLFW_MOUSE_BUTTON_1))//if the user selects a building it is recorded and sets isPlacingBuilding to true
							{
								hoverOverABuildingInList = false;
								isPlacingBuilding = true;
								PlacingBuildingID = j;
								hoverBuildingSize.x = _listOfAllBuildings->at(j)->getSize().x;
								hoverBuildingSize.y = _listOfAllBuildings->at(j)->getSize().y;
								while (_selectedUnits->empty() == false)
								{
									for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
									{
										_selectedUnits->erase(i);
										break;
									}
								}
								selectingSingleUnits = false;
								hasUnitsSelected = false;
								mouseSelectionClicked = false;
								isBuilderSelected = false;
								_hasBuildingSelected = false;
								selectedBuilderID = -1;
							}
							break;
						}
						else
						{
							hoverOverABuildingInList = false;
						}
					}
				}//TODO add combat
			}
			//checks if the stop button was pressed and stops selected units instantly
			if (_input->getX() > _width - mapWidth - 10 - (TEXTUREWIDTH * 3) && _input->getX() < _width - mapWidth - 10 && _input->getY() > (2 * _height / 3) + 25 && _input->getY() < (2 * _height / 3) + 25 + (TEXTUREHEIGHT * 3))
			{
				hoverOverStop = true;
				if (_input->getMouseState(GLFW_MOUSE_BUTTON_1))
				{
					for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
					{
						(*i)->setMoving(false);
						(*i)->clearPath();
						hoverOverStop = false;
					}
				}
			}
			else
			{
				hoverOverStop = false;
			}
			//checks if one unit is selected and if it is a builder
			if (_selectedUnits->size() == 1 && _selectedUnits->at(0)->getType() == BUILDER_TYPE)
			{
				isBuilderSelected = true;
				selectedBuilderID = _selectedUnits->at(0)->getID();
				for (std::vector<Builder*>::iterator i = _builders->begin(); i != _builders->end(); i++)
				{
					if ((*i)->getID() == selectedBuilderID)
					{
						selectedBuilder = *i;
						break;
					}
				}
			}

			if (_input->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				while (_selectedUnits->empty() == false)
				{
					for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
					{
						_selectedUnits->erase(i);
						break;
					}
				}
				selectingSingleUnits = false;
				_hasBuildingSelected = false;
				hasUnitsSelected = false;
				mouseSelectionClicked = false;
				isBuilderSelected = false;
				selectedBuilderID = -1;
				_hasBuildingListItemSelected = false;
				hoverOverABuildingInList = false;
			}
			if (_input->getMouseState(GLFW_MOUSE_BUTTON_2) && _input->getY() < (2 * _height / 3))
			{
				if (_tiles[(int)((camerax + _input->getX()) / TEXTUREWIDTH)][(int)(cameray + _input->getY()) / TEXTUREHEIGHT]->getTravelable() == true)
				{
					for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
					{
						//std::thread path(&Unit::findPath, (*i),_tiles, _tiles[(int)((camerax + _input->getX()) / TEXTUREWIDTH)][(int)(cameray + _input->getY()) / TEXTUREHEIGHT], mapWidth, mapHeight);
						//path.join();
						Unit::findPath((*i), _tiles, _tiles[(int)((camerax + _input->getX()) / TEXTUREWIDTH)][(int)(cameray + _input->getY()) / TEXTUREHEIGHT], mapWidth, mapHeight, false, _islandMap);
					}
					for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
					{
						for (std::vector<Builder*>::iterator a = _builders->begin(); a != _builders->end(); a++)
						{
							if ((*a)->getID() == (*i)->getID())
							{
								(*a)->setIsBuilding(false);
								((Builder*)(*i))->setIsBuilding(false);
								break;
							}
						}
					}
					while (_selectedUnits->empty() == false)
					{
						for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
						{
							_selectedUnits->erase(i);
							break;
						}
					}
					selectingSingleUnits = false;
					hasUnitsSelected = false;
					_hasBuildingSelected = false;
					mouseSelectionClicked = false;
					isBuilderSelected = false;
					selectedBuilderID = -1;
				}
				else
				{
					for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
					{
						for (std::vector<Building*>::iterator c = _buildings->begin(); c != _buildings->end(); c++)
						{
							int x = camerax + _input->getX();
							int y = cameray + _input->getY();
							int xx = (*c)->getPosition().x;
							int yy = (*c)->getPosition().y;
							if (x > xx && x < xx + (*c)->getSize().x && y > yy && y < yy + (*c)->getSize().y)
							{
								_destIsBuilding = true;
								destBuilding = (*c);
								Unit::findPath((*i), _tiles, _tiles[(int)((camerax + _input->getX()) / TEXTUREWIDTH)][(int)(cameray + _input->getY()) / TEXTUREHEIGHT], mapWidth, mapHeight, true, _islandMap);
								if (_selectedUnits->size() == 1)
								{
									if (_selectedUnits->at(0)->getType() == BUILDER_TYPE)
									{
										((Builder*)(*i))->setBuilding(*c);
										((Builder*)(*i))->setIsBuilding(true);
										for (std::vector<Builder*>::iterator a = _builders->begin(); a != _builders->end(); a++)
										{
											if ((*a)->getID() == _selectedUnits->at(0)->getID())
											{
												(*a) = (Builder*)(*i);
												break;
											}
										}
									}
								}
							}
						}
					}
					//std::cout << "Destination is not passable terrain (" << ((camerax + _input->getX()) / TEXTUREWIDTH) << "," << ((cameray + _input->getY()) / TEXTUREHEIGHT) << ")\n";
				}
			}
			else if (_input->getMouseState(GLFW_MOUSE_BUTTON_2) && _input->getY() > (2 * _height / 3))
			{
				for (std::vector<Builder*>::iterator a = _builders->begin(); a != _builders->end(); a++)
				{
					if ((*a)->getID() == selectedBuilderID)
					{
						(*a)->setBuilding(false);
						for (std::vector<Unit*>::iterator i = _units->begin(); i != _units->end(); i++)
						{
							if ((*i)->getID() == (*a)->getID())
							{
								(*i) = (*a);
								break;
							}
						}
						break;
					}
				}
				float xpos = abs(_input->getX() - tempx);
				float ypos = abs(_input->getY() - tempy);
				std::cout << "Coords (" << xpos << "," << ypos << ") ...\n";
				if (_input->getX() > tempx && _input->getX() < tempx + mapWidth && _input->getY() > tempy && _input->getY() < tempy + mapHeight)
				{
					//if (_tiles[(int)xpos][(int)ypos]->getTravelable() == true)
					{
						for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
						{
							//std::thread path(&Unit::findPath, (*i),_tiles, _tiles[(int)((camerax + _input->getX()) / TEXTUREWIDTH)][(int)(cameray + _input->getY()) / TEXTUREHEIGHT], mapWidth, mapHeight);
							//path.join();
						}
						while (_selectedUnits->empty() == false)
						{
							for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
							{
								_selectedUnits->erase(i);
								break;
							}
						}
						selectingSingleUnits = false;
						hasUnitsSelected = false;
						_hasBuildingSelected = false;
						mouseSelectionClicked = false;
						isBuilderSelected = false;
						selectedBuilderID = -1;
					}
				}
				else
				{
					//std::cout << "Destination is not passable terrain (" << ((camerax + _input->getX()) / TEXTUREWIDTH) << "," << ((cameray + _input->getY()) / TEXTUREHEIGHT) << ")";
				}
			}
		}
		else if (_input->getMouseState(GLFW_MOUSE_BUTTON_1) && mouseSelectionClicked == false && mouseDown == false && _input->getY() < (2 * _height / 3) && selectingSingleUnits == false && hasUnitsSelected == false && !isPlacingBuilding)
		{
			mouseClicked.x = camerax + _input->getX();
			mouseClicked.y = cameray + _input->getY();
			mouseSelectionClicked = true;
			mouseDown = true;
			_hasBuildingListItemSelected = false;
			hoverOverABuildingInList = false;
		}
		else if (mouseSelectionClicked == true && _input->getMouseState(GLFW_MOUSE_BUTTON_1) == false && _input->getY() < (2 * _height / 3) && selectingSingleUnits == false && hasUnitsSelected == false && !isPlacingBuilding)
		{
			mouseSelectionClicked = false;
			int startx = 0;
			int starty = 0;
			int endx = 0;
			int endy = 0;
			if (mouseClicked.x > camerax + _input->getX())
			{
				startx = camerax + _input->getX();
				endx = mouseClicked.x;
			}
			else
			{
				startx = mouseClicked.x;
				endx = camerax + _input->getX();
			}
			if (mouseClicked.y > cameray + _input->getY())
			{
				starty = cameray + _input->getY();
				endy = mouseClicked.y;
			}
			else
			{
				starty = mouseClicked.y;
				endy = cameray + _input->getY();
			}
			for (std::vector<Unit*>::iterator i = _units->begin(); i != _units->end(); i++)
			{
				if ((*i)->getPosition().x > startx && (*i)->getPosition().x < endx && (*i)->getPosition().y > starty && (*i)->getPosition().y < endy)
				{
					_selectedUnits->push_back(*i);
				}
				else if ((*i)->getPosition().x + TEXTUREWIDTH > startx && (*i)->getPosition().x + TEXTUREWIDTH < endx && (*i)->getPosition().y + TEXTUREHEIGHT > starty && (*i)->getPosition().y + TEXTUREHEIGHT < endy)
				{
					_selectedUnits->push_back(*i);
				}
				else if ((*i)->getPosition().x + TEXTUREWIDTH> startx && (*i)->getPosition().x + TEXTUREWIDTH < endx && (*i)->getPosition().y > starty && (*i)->getPosition().y < endy)
				{
					_selectedUnits->push_back(*i);
				}
				else if ((*i)->getPosition().x > startx && (*i)->getPosition().x < endx && (*i)->getPosition().y + TEXTUREHEIGHT > starty && (*i)->getPosition().y + TEXTUREHEIGHT< endy)
				{
					_selectedUnits->push_back(*i);
				}
				else if ((*i)->getPosition().x + (TEXTUREWIDTH / 2) > startx && (*i)->getPosition().x + (TEXTUREWIDTH / 2) < endx && (*i)->getPosition().y + (TEXTUREHEIGHT / 2) > starty && (*i)->getPosition().y + (TEXTUREHEIGHT / 2) < endy)
				{
					_selectedUnits->push_back(*i);
				}
			}
			mouseDown = false;
			if (_selectedUnits->empty() == false)
			{
				hasUnitsSelected = true;
			}
			else{
				hasUnitsSelected = false;
			}
		}
		if (hasUnitsSelected == false && _input->getMouseState(GLFW_MOUSE_BUTTON_1))
		{
			for (std::vector<Building*>::iterator i = _buildings->begin(); i != _buildings->end(); i++)
			{
				int x = (*i)->getPosition().x;
				int y = (*i)->getPosition().y;
				int sizex = (*i)->getSize().x;
				int sizey = (*i)->getSize().y;

				if (mousex > x && mousex < x + sizex && mousey > y && mousey < y + sizey)
				{
					_selectedBuilding = (*i);
					_hasBuildingSelected = true;
				}
				else if (mousex + 2 > x && mousex + 2 < x + sizex && mousey > y && mousey < y + sizey)
				{
					_selectedBuilding = (*i);
					_hasBuildingSelected = true;
				}
				else if (mousex > x && mousex < x + sizex && mousey + 2 > y && mousey + 2 < y + sizey)
				{
					_selectedBuilding = (*i);
					_hasBuildingSelected = true;
				}
				else if (mousex + 2 > x && mousex + 2 < x + sizex && mousey + 2 > y && mousey + 2 < y + sizey)
				{
					_selectedBuilding = (*i);
					_hasBuildingSelected = true;
				}
				//if (po.isOverlapping(buil))
				//{
				//	std::cout << "Mouse Selected Building at Mx: " << po.getPosition().x << ", My: " << po.getPosition().y << " Bx: " << buil.getPosition().x << ", By: " << buil.getPosition().y << std::endl;
				//	std::cout << "Size " << buil.getSize().x << ", " << buil.getSize().y << std::endl;
				//	_selectedBuilding = (*i);
				//	_hasBuildingSelected = true;
				//}
			}
		}
		else
		{
			if (isPlacingBuilding || hasUnitsSelected || (_input->getMouseState(GLFW_MOUSE_BUTTON_2) && _input->getY() < (2 * _height / 3) + 25))
			{
				_hasBuildingSelected = false;
			}
		}
		//temp
		for (std::vector<Building*>::iterator i = _buildings->begin(); i != _buildings->end(); i++)
		{
			for (std::vector<Unit*>::iterator a = (*i)->getQueue()->begin(); a != (*i)->getQueue()->begin(); a++)
			{
				if ((*a)->getIsBuilt() == false)
				{
					(*a)->build();
					break;
				}
				else{
					_units->push_back((*a));
					(*i)->getQueue()->erase((*i)->getQueue()->begin());
					_units->at(_units->size() - 1)->setID(_units->at(_units->size() - 2)->getID() + 1);
					break;
				}
			}
			Vector2f p = (*i)->getPosition();
			Vector2f s = (*i)->getSize();
			for (int x = (p.x) / TEXTUREWIDTH; x < (p.x + s.x) / TEXTUREWIDTH; x++)
			{
				for (int y = (p.y) / TEXTUREHEIGHT; y < (p.y + s.y) / TEXTUREHEIGHT; y++)
				{
					if ((*i)->getType() == BRIDGE_ID)
					{
						_tiles[x][y]->changeToBridge(_textures->getBridgeTexture());
					}
					else
					{
						_tiles[x][y]->setTravelable(false);
					}
				}
			}
		}
		//end temp

		int count = 0;
		for (std::vector<Unit*>::iterator i = _units->begin(); i != _units->end(); i++)
		{
			if ((*i)->getMoving())
			{
				(*i)->move(_units);
			}
			count++;
		}
		for (std::vector<Builder*>::iterator i = _builders->begin(); i != _builders->end(); i++)
		{
			if ((*i)->getIsBuiding() && (*i)->getPosition().x > (*i)->getBuilding()->getPosition().x - TEXTUREWIDTH && (*i)->getPosition().x < (*i)->getBuilding()->getPosition().x + (*i)->getBuilding()->getSize().x + TEXTUREWIDTH && (*i)->getPosition().y >(*i)->getBuilding()->getPosition().y - TEXTUREHEIGHT && (*i)->getPosition().y < (*i)->getBuilding()->getPosition().y + (*i)->getBuilding()->getSize().y + TEXTUREHEIGHT)
			{
				(*i)->build();
			}
			if ((*i)->getIsBuiding() && (*i)->getBuilding()->getIsBuilt() == false && (*i)->getType() == BRIDGE_ID)
			{
				(*i)->getBuilding()->setIsBuilding(true);
				std::vector<std::string>* islands = new std::vector<std::string>();
				Vector2f pos = newVector2f((int)(*i)->getPosition().x / TEXTUREWIDTH, (int)(*i)->getPosition().y / TEXTUREHEIGHT);
				std::vector<Vector2f>* toCheck = new std::vector<Vector2f>();
				std::vector<Vector2f>* checked = new std::vector<Vector2f>();
				toCheck->push_back(pos);
				while (toCheck->empty() == false)
				{
					Vector2f p = toCheck->at(0);
					if (_tiles[(int)p.x - 1][(int)p.y - 1]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x - 1, p.y - 1)) && !check(checked, newVector2f(p.x - 1, p.y - 1)))
						{
							toCheck->push_back(newVector2f(p.x - 1, p.y - 1));
						}
					}
					if (_tiles[(int)p.x][(int)p.y - 1]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x, p.y - 1)) && !check(checked, newVector2f(p.x, p.y - 1)))
						{
							toCheck->push_back(newVector2f(p.x, p.y - 1));
						}
					}
					if (_tiles[(int)p.x + 1][(int)p.y - 1]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x + 1, p.y - 1)) && !check(checked, newVector2f(p.x + 1, p.y - 1)))
						{
							toCheck->push_back(newVector2f(p.x + 1, p.y - 1));
						}
					}
					if (_tiles[(int)p.x - 1][(int)p.y]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x - 1, p.y)) && !check(checked, newVector2f(p.x - 1, p.y)))
						{
							toCheck->push_back(newVector2f(p.x - 1, p.y));
						}
					}
					if (_tiles[(int)p.x + 1][(int)p.y]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x + 1, p.y - 1)) && !check(checked, newVector2f(p.x + 1, p.y - 1)))
						{
							toCheck->push_back(newVector2f(p.x + 1, p.y));
						}
					}
					if (_tiles[(int)p.x - 1][(int)p.y + 1]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x - 1, p.y + 1)) && !check(checked, newVector2f(p.x - 1, p.y + 1)))
						{
							toCheck->push_back(newVector2f(p.x - 1, p.y + 1));
						}
					}
					if (_tiles[(int)p.x][(int)p.y + 1]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x, p.y + 1)) && !check(checked, newVector2f(p.x, p.y + 1)))
						{
							toCheck->push_back(newVector2f(p.x, p.y + 1));
						}
					}
					if (_tiles[(int)p.x + 1][(int)p.y + 1]->getType() == BRIDGE)
					{
						if (!check(toCheck, newVector2f(p.x + 1, p.y + 1)) && !check(checked, newVector2f(p.x + 1, p.y + 1)))
						{
							toCheck->push_back(newVector2f(p.x + 1, p.y + 1));
						}
					}



					if (_tiles[(int)p.x - 1][(int)p.y - 1]->getType() != BRIDGE && _tiles[(int)p.x - 1][(int)p.y - 1]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x - 1][(int)p.y - 1]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x - 1][(int)p.y - 1]->getIslandID());
						}
					}
					if (_tiles[(int)p.x][(int)p.y - 1]->getType() == BRIDGE && _tiles[(int)p.x][(int)p.y - 1]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x][(int)p.y - 1]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x][(int)p.y - 1]->getIslandID());
						}
					}
					if (_tiles[(int)p.x + 1][(int)p.y - 1]->getType() == BRIDGE && _tiles[(int)p.x + 1][(int)p.y - 1]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x + 1][(int)p.y - 1]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x + 1][(int)p.y - 1]->getIslandID());
						}
					}
					if (_tiles[(int)p.x - 1][(int)p.y]->getType() == BRIDGE && _tiles[(int)p.x - 1][(int)p.y]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x - 1][(int)p.y]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x - 1][(int)p.y]->getIslandID());
						}
					}
					if (_tiles[(int)p.x + 1][(int)p.y]->getType() == BRIDGE && _tiles[(int)p.x + 1][(int)p.y]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x + 1][(int)p.y]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x + 1][(int)p.y]->getIslandID());
						}
					}
					if (_tiles[(int)p.x - 1][(int)p.y + 1]->getType() == BRIDGE && _tiles[(int)p.x - 1][(int)p.y + 1]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x - 1][(int)p.y + 1]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x - 1][(int)p.y + 1]->getIslandID());
						}
					}
					if (_tiles[(int)p.x][(int)p.y + 1]->getType() == BRIDGE && _tiles[(int)p.x][(int)p.y + 1]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x][(int)p.y + 1]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x][(int)p.y + 1]->getIslandID());
						}
					}
					if (_tiles[(int)p.x + 1][(int)p.y + 1]->getType() == BRIDGE && _tiles[(int)p.x + 1][(int)p.y + 1]->getTravelable())
					{
						if (!check(islands, _tiles[(int)p.x + 1][(int)p.y + 1]->getIslandID()))
						{
							islands->push_back(_tiles[(int)p.x + 1][(int)p.y + 1]->getIslandID());
						}
					}
					checked->push_back(toCheck->at(0));
					toCheck->erase(toCheck->begin());
				}
				for (std::vector<IslandListItem>::iterator c = _islandMap->begin(); c != _islandMap->end(); c++)
				{
					if (check(islands, (*c).getIslandID1()))
					{
						islands->push_back((*c).getIslandID2());
					}
				}
				for (std::vector<std::string>::iterator a = islands->begin(); a != islands->end(); a++)
				{
					for (std::vector<std::string>::iterator b = islands->begin(); b != islands->end(); b++)
					{
						_islandMap->push_back(IslandListItem((*a), (*b)));
					}
				}
			}
		}
	}
	else if (state == OPTIONS)
	{
		if (_input->getX() > 0 && _input->getX() < 32 * 6)
		{
			if (_input->getY() > /*testBlock->getSize()*/ 32 * 2 && _input->getY() < /*testBlock->getSize()*/ 32 * 4 && _input->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				std::ofstream file;
				file.open("settings.txt");
				file << "1366\n";
				file << "768\n";
				file.close();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				// TODO:: Restart CODE
			}
			else if (_input->getY() > /*testBlock->getSize()*/ 32 * 4 && _input->getY() < /*testBlock->getSize()*/ 32 * 6 && _input->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				std::ofstream file;
				file.open("settings.txt");
				file << "1920\n";
				file << "1080\n";
				file.close();
				std::this_thread::sleep_for(std::chrono::seconds(1));
				// TODO:: Restart CODE
			}
		}


		//GFX::drawRect(128, 64, 128, 32 * 7, _textures->getEnabledSecondTexture());

		if (_input->getX() > 128 && _input->getX() < 256 && _input->getY() > 32 * 7 && _input->getY() < (32 * 7) + 64)
		{
			if (_input->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				vsync = !vsync;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
		if (_input->getX() > 128 && _input->getX() < 256 && _input->getY() > 32 * 9 && _input->getY() < (32 * 9) + 64)
		{
			if (_input->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				msaa = !msaa;
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}

		if (_input->getKeyState(GLFW_KEY_ESCAPE))
		{
			state = previous;
			previous = OPTIONS;
		}
	}
	else if (state == PAUSE_MENU)
	{
		resumeButton->update(_input);
		optionsPauseMenu->update(_input);
		exitPauseMenu->update(_input);

		if (resumeButton->isButton1Clicked(_input))
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			previous = PAUSE_MENU;
			state = GAME;
			std::cout << "Resume Clicked\n";
		}
		if (optionsPauseMenu->isButton1Clicked(_input))
		{
			std::cout << "OPTIONS Button Pressed\n";
			std::this_thread::sleep_for(std::chrono::seconds(1));
			state = OPTIONS;
			previous = PAUSE_MENU;
		}
		if (exitPauseMenu->isButton1Clicked(_input))
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			previous = PAUSE_MENU;
			state = MAIN_MENU;
			std::cout << "Exit Clicked\n";
		}
	}
	else if (state == LOADING)
	{
		if (previous == MAIN_MENU && next == GAME && !loading)
		{
			std::thread world (&Game::loadWorld,this);
			world.detach();
			loading = true;
			std::cout << "Loading\n";
		}
		if (loaded)
		{
			state = GAME;
			next = GAME;
		}
	}
	if (_input->getKeyState(GLFW_KEY_1))
	{
		exit(0);
	}
}

void Game::loadWorld()
{
	//system("WorldGenerator.jar 256");
	//_world = new World("C:\\Users\\Craig\\Dropbox\\C++ Games\\3DGame01\\3DGame01\\res\\Worlds\\level\\test0.cr", _textures);
	std::ifstream file(".\\res\\Worlds\\level\\004.cr");
	//std::ifstream file(".\\res\\Worlds\\level\\test2.cr");
	int counter = 0;
	int lineCounter = 0;
	std::string line;
	int id = 0;
	while (std::getline(file, line))
	{
		std::istringstream buf(line);
		std::istream_iterator<std::string> beg(buf), end;
		std::vector<std::string> tokens(beg, end);
		int colCounter = 0;
		for (auto& s : tokens)
		{
			std::string s1 = s.substr(0, 4);
			std::string s2 = s.substr(4, 5);
			if (s2 == "0")
			{
				_tiles[colCounter][lineCounter] = new Tile(id,newVector2f(colCounter * TEXTUREWIDTH, lineCounter * TEXTUREHEIGHT), _menuTextures->getBetterGrassTexture(), true, newVector2f(colCounter, lineCounter), GRASS,s1);
				//std::cout << "Add DirtBlock at : (" << colCounter * _textureSize << "," << lineCounter * _textureSize << ")\n";
			}
			else if (s2 == "1")
			{
				_tiles[colCounter][lineCounter] = new Tile(id, newVector2f(colCounter * TEXTUREWIDTH, lineCounter * TEXTUREHEIGHT), _menuTextures->getDirtTexture(), true, newVector2f(colCounter, lineCounter), DIRT, s1);
				//std::cout << "Add AirBlock at : (" << colCounter * _textureSize << "," << lineCounter * _textureSize << ")\n";
			}
			else if (s2 == "2")
			{
				_tiles[colCounter][lineCounter] = new Tile(id, newVector2f(colCounter * TEXTUREWIDTH, lineCounter * TEXTUREHEIGHT), _menuTextures->getWaterTexture(), false, newVector2f(colCounter, lineCounter), WATER, s1);
			}
			else if (s2 == "3")
			{
				_tiles[colCounter][lineCounter] = new Tile(id, newVector2f(colCounter * TEXTUREWIDTH, lineCounter * TEXTUREHEIGHT), _menuTextures->getMountainTexture(), false, newVector2f(colCounter, lineCounter), MOUNTAIN, s1);
			}

			counter++;
			colCounter++;
			id++;
		}
		mapWidth = lineCounter - 1;
		worldWidth = mapWidth;
		lineCounter++;
	}
	mapHeight = lineCounter - 1;
	worldHeight = mapHeight;
	loaded = true;
	std::cout << "Done!\n";
}

void Game::render()
{
	if (state == MAIN_MENU)
	{
		//GFX::drawRect(_width, _height, 0, 0, _textures->getBackgroundTestTexture());
		playButton->draw();
		optionsButton->draw();
		exitButton->draw();
	}
	else if (state == GAME)
	{
		if (_hasGeneratedMiniMap == false){
			return;
		}
		int camerax = -_camera->getPosition().x;
		int cameray = -_camera->getPosition().y;
		int cameramx = (-_camera->getPosition().x) + _width;
		int cameramy = (-_camera->getPosition().y) + (2 * _height / 3);
		if (camerax <= 0)
		{
			_camera->setPosition(newVector2f(0, _camera->getPosition().y));
			camerax = 0;
		}
		if (cameray <= 0)
		{
			_camera->setPosition(newVector2f(_camera->getPosition().x, 0));
			cameray = 0;
		}
		if (camerax + _width >= mapWidth * TEXTUREWIDTH)
		{
			_camera->setPosition(newVector2f(-(mapWidth * TEXTUREWIDTH - _width), _camera->getPosition().y));
		}
		if (cameray + (2 * _height / 3) >= mapHeight * TEXTUREHEIGHT)
		{
			_camera->setPosition(newVector2f(_camera->getPosition().x, -(mapHeight * TEXTUREHEIGHT - (2 * _height / 3))));
		}
		camerax = -_camera->getPosition().x;
		cameray = -_camera->getPosition().y;
		cameramx = (-_camera->getPosition().x) + _width;
		cameramy = (-_camera->getPosition().y) + (2 * _height / 3);
		_camera->update();
		glTranslatef(_camera->getOffset().x, _camera->getOffset().y, 0);
		//if (cameray / TEXTUREHEIGHT >= 0 && cameray / TEXTUREHEIGHT < mapHeight && camerax / TEXTUREWIDTH >= 0 && camerax / TEXTUREWIDTH < mapWidth && cameramx / TEXTUREWIDTH > 0 && cameramx / TEXTUREWIDTH < mapWidth && cameramy / TEXTUREHEIGHT > 0 && cameramy / TEXTUREHEIGHT < mapHeight)
		{
			for (int y = cameray / TEXTUREHEIGHT; y < (cameramy + TEXTUREHEIGHT) / TEXTUREHEIGHT; y++)
			{
				for (int x = camerax / TEXTUREWIDTH; x < (cameramx + TEXTUREWIDTH) / TEXTUREWIDTH; x++)
				{
					if (x > mapWidth || x < 0 || y < 0 || y > mapHeight)
					{

					}
					else
					{
						_tiles[x][y]->draw();
					}
				}
			}
		}
		//else
		{
			//	std::cout << "Can't draw out of bounds - Camerax: " << camerax << " Cameray: " << cameray << " Cameramx: " << cameramx << " Cameramy: " << cameramy << "\n";
		}
		for (std::vector<Building*>::iterator i = _buildings->begin(); i != _buildings->end(); i++)
		{
			(*i)->draw();
			if ((*i)->getIsBuilt() == false)
			{
				if ((*i)->getPercentageBuilt() < 10)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding0Percent());
				}
				else if ((*i)->getPercentageBuilt() < 20)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding10Percent());
				}
				else if ((*i)->getPercentageBuilt() < 30)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding20Percent());
				}
				else if ((*i)->getPercentageBuilt() < 40)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding30Percent());
				}
				else if ((*i)->getPercentageBuilt() < 50)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding40Percent());
				}
				else if ((*i)->getPercentageBuilt() < 60)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding50Percent());
				}
				else if ((*i)->getPercentageBuilt() < 70)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding60Percent());
				}
				else if ((*i)->getPercentageBuilt() < 80)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding70Percent());
				}
				else if ((*i)->getPercentageBuilt() < 90)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding80Percent());
				}
				else if ((*i)->getPercentageBuilt() < 100)
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding90Percent());
				}
				else
				{
					GFX::drawRect((*i)->getSize().x, (*i)->getSize().y, (*i)->getPosition().x, (*i)->getPosition().y, _textures->getBuilding100Percent());
				}
			}
			else{
				(*i)->build();
			}
		}
		for (std::vector<Unit*>::iterator i = _units->begin(); i != _units->end(); i++)
		{
			(*i)->draw();
		}
		if (mouseSelectionClicked)
		{
			//GFX::drawRect((camerax + _input->getX() - mouseClicked.x), (cameray + _input->getY() - mouseClicked.y), mouseClicked.x, mouseClicked.y, _textures->getSelectionBox());
			GFX::drawRect(camerax + _input->getX() - mouseClicked.x, 1, mouseClicked.x, mouseClicked.y, _textures->getGreenHealthTexture());
			GFX::drawRect(1, cameray + _input->getY() - mouseClicked.y, mouseClicked.x, mouseClicked.y, _textures->getGreenHealthTexture());
			GFX::drawRect(camerax + _input->getX() - mouseClicked.x, 1, mouseClicked.x, cameray + _input->getY(), _textures->getGreenHealthTexture());
			GFX::drawRect(1, cameray + _input->getY() - mouseClicked.y, camerax + _input->getX(), mouseClicked.y, _textures->getGreenHealthTexture());
		}
		if (hasUnitsSelected)
		{
			int x = (camerax + _input->getX()) / TEXTUREWIDTH;
			int y = (cameray + _input->getY()) / TEXTUREHEIGHT;
			GFX::drawRect(TEXTUREWIDTH, TEXTUREHEIGHT, x * TEXTUREWIDTH, y * TEXTUREHEIGHT, _textures->getHoverTexture());
			for (std::vector<Unit*>::iterator i = _selectedUnits->begin(); i != _selectedUnits->end(); i++)
			{
				int health = (*i)->getHealth();
				int length = 100 / TEXTUREWIDTH;
				if (health / TEXTUREWIDTH > (2 * length / 3))
				{
					for (int x = 0; x < TEXTUREWIDTH; x++)
					{
						if (x <= health / length)
						{
							GFX::drawRect(1, 1, (*i)->getPosition().x + x, (*i)->getPosition().y + 1, _textures->getGreenHealthTexture());
						}
						else
						{
							GFX::drawRect(1, 1, (*i)->getPosition().x + x, (*i)->getPosition().y + 1, _textures->getRedHealthTexture());
						}
					}
				}
				else
				{
					for (int x = 0; x < TEXTUREWIDTH; x++)
					{
						if (x <= health / length)
						{
							GFX::drawRect(1, 1, (*i)->getPosition().x + x, (*i)->getPosition().y + 1, _textures->getYellowHealthTexture());
						}
						else
						{
							GFX::drawRect(1, 1, (*i)->getPosition().x + x, (*i)->getPosition().y + 1, _textures->getRedHealthTexture());
						}
					}
				}
			}
		}
		GFX::drawRect(_width, _width, camerax + 0, cameray + (2 * _height / 3), _textures->getControlsBackground());
		if (hasUnitsSelected)
		{
			GFX::drawRect(TEXTUREWIDTH * 3, TEXTUREHEIGHT * 3, camerax + _width - mapWidth - 10 - (TEXTUREWIDTH * 3), cameray + (2 * _height / 3) + 25, _textures->getStopTexture());
		}
		if (hoverOverStop)
		{
			GFX::drawRect(TEXTUREWIDTH * 3, TEXTUREHEIGHT * 3, camerax + _width - mapWidth - 10 - (TEXTUREWIDTH * 3), cameray + (2 * _height / 3) + 25, _textures->getHoverTexture());
		}
		if (isBuilderSelected)
		{
			if (!selectedBuilder->getIsBuiding())
			{
				int c = 0;
				for (std::vector<Building*>::iterator i = _listOfAllBuildings->begin(); i != _listOfAllBuildings->end(); i++)
				{
					GFX::drawRect(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2, camerax + (TEXTUREWIDTH * 10 + ((2 * c) * TEXTUREWIDTH)), cameray + (2 * _height / 3) + 25, (*i)->getTexture());
					c++;
				}
				//GFX::drawRect(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2, camerax + TEXTUREWIDTH * 10, cameray + (2 * _height / 3) + 25, _textures->getBuildingFactoryTexture());
			}
		}
		if (hoverOverABuildingInList)
		{
			//std::cout << "Hover is: " << hoverOverABuildingInList << " ID: " << idOfBuildingInList << std::endl;
			GFX::drawRect(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2, camerax + (TEXTUREWIDTH * 10 + ((2 * idOfBuildingInList) * TEXTUREWIDTH)), cameray + (2 * _height / 3) + 25, _textures->getHoverTexture());
		}
		if (_hasBuildingSelected)
		{
			if (_selectedBuilding != NULL)
			{
				int c = 0;
				for (std::vector<BuildingItemsListItem*>::iterator i = _testFactory1->begin(); i != _testFactory1->end(); i++)
				{
					GFX::drawRect(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2, camerax + (TEXTUREWIDTH * 10 + ((2 * c) * TEXTUREWIDTH)), cameray + (2 * _height / 3) + 25, (*i)->getTexture());
					c++;
				}
				for (std::vector<Building*>::iterator i = _buildings->begin(); i != _buildings->end(); i++)
				{
					if ((*i)->getId() == _selectedBuilding->getId())
					{
						int counter = 0;
						for (std::vector<Unit*>::iterator a = (*i)->getQueue()->begin(); a != (*i)->getQueue()->end(); a++)
						{
							GFX::drawRect(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2, camerax + 10 + (counter * TEXTUREWIDTH * 2), cameray + 2 * (_height / 3) + 10);
							counter++; 
						}
						break;
					}
				}
			}
		}
		if (_hasBuildingListItemSelected)
		{
			GFX::drawRect(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2, camerax + (TEXTUREWIDTH * 10 + ((2 * _idOfBuildingItemHover) * TEXTUREWIDTH)), cameray + (2 * _height / 3) + 25, _textures->getHoverTexture());
		}

		if (isPlacingBuilding)
		{
			Building* buildingToPlace = NULL;
			buildingToPlace = _listOfAllBuildings->at(PlacingBuildingID);
			if (PlacingBuildingID == BRIDGE_ID)
			{
				Vector2f position = newVector2f((int)((camerax + _input->getX()) / TEXTUREWIDTH), (int)((cameray + _input->getY()) / TEXTUREHEIGHT));
				buildingToPlace->setPosition(newVector2f(position.x * TEXTUREWIDTH,position.y * TEXTUREHEIGHT));
				bool cont = true;
				if (_tiles[(int)position.x][(int)position.y]->getTravelable() == true)
				{
					cont = false;
				}
				if (canPlaceBuildingThere == false && cont)
				{
					GFX::drawRect(buildingToPlace->getSize().x + 4, buildingToPlace->getSize().y + 4, ((int)(camerax + _input->getX())/TEXTUREWIDTH) * TEXTUREHEIGHT, ((int)(cameray + _input->getY()) / TEXTUREHEIGHT) * TEXTUREHEIGHT, _textures->getGreenHoverTexture());
				}
				else
				{
					GFX::drawRect(buildingToPlace->getSize().x + 4, buildingToPlace->getSize().y + 4, ((int)(camerax + _input->getX()) / TEXTUREWIDTH) * TEXTUREHEIGHT, ((int)(cameray + _input->getY()) / TEXTUREHEIGHT) * TEXTUREHEIGHT, _textures->getRedHoverTexture());
				}
				buildingToPlace->draw();
			}
			else
			{
				buildingToPlace->setPosition(newVector2f(camerax + _input->getX(), cameray + _input->getY()));
				//if (PlacingBuildingID == 0)
				//{
				//	buildingToPlace = new Building(newVector2f(camerax + _input->getX(),cameray + _input->getY()), newVector2f(TEXTUREWIDTH * 2, TEXTUREHEIGHT * 2), "TEST Building", PlacingBuildingID, _textures->getBuildingFactoryTexture());
				//}
				if (canPlaceBuildingThere == true)
				{
					GFX::drawRect(buildingToPlace->getSize().x + 4, buildingToPlace->getSize().y + 4, camerax + _input->getX(), cameray + _input->getY(), _textures->getGreenHoverTexture());
				}
				else
				{
					GFX::drawRect(buildingToPlace->getSize().x + 4, buildingToPlace->getSize().y + 4, camerax + _input->getX(), cameray + _input->getY(), _textures->getRedHoverTexture());
				}
				buildingToPlace->draw();
			}			
		}
		int startx = _width - mapWidth - 10;
		int starty = (2 * _height / 3) + 25;
		//GFX::drawRect(256, 256, startx + camerax, starty + cameray, _textures->getGeneratedMap());
		for (int y = 0; y < mapHeight; y+=4)
		{
			for (int x = 0; x < mapWidth; x+=4)
			{
				int upLeft = _tiles[x][y]->getType();
				int upRight = _tiles[x + 1][y]->getType();
				int botLeft = _tiles[x][y + 1]->getType();
				int botRight = _tiles[x + 1][y + 1]->getType();
				if (upLeft == upRight || upLeft == botLeft || upLeft == botRight)
				{
					GFX::drawRect(4, 4, startx + camerax + x, starty + cameray + y, _tiles[x][y]->getTexture());
				}
				else if (upRight == botLeft || upRight == botRight)
				{
					GFX::drawRect(4, 4, startx + camerax + x, starty + cameray + y, _tiles[x + 1][y]->getTexture());
				}
				else if (botLeft == botRight){
					GFX::drawRect(4, 4, startx + camerax + x, starty + cameray + y, _tiles[x][y + 1]->getTexture());
				}
				else{
					GFX::drawRect(4, 4, startx + camerax + x, starty + cameray + y, _tiles[x + 1][y + 1]->getTexture());
				}
			}
		}
		GFX::drawRect(_width / TEXTUREWIDTH, (2 * _height / 3) / TEXTUREHEIGHT, startx + camerax + (camerax / TEXTUREWIDTH), starty + cameray + (cameray / TEXTUREHEIGHT), _textures->getMinimapSquare());
		for (std::vector<Unit*>::iterator i = _units->begin(); i != _units->end(); i++)
		{
			GFX::drawRect(1, 1, startx + (int)((*i)->getPosition().x / TEXTUREWIDTH) + camerax, starty + (int)((*i)->getPosition().y / TEXTUREHEIGHT) + cameray, _textures->getGrassTopTexture());
		}
	}
	else if (state == OPTIONS)
	{
		//GFX::drawRect(_width, _height, 0, 0, _textures->getBackgroundTestTexture());
		GFX::drawString(0, /*testBlock->getSize()*/ 32 * 4, "1366 X 768", 1.0f, 1.0f, 1.0f);
		GFX::drawString(0, /*testBlock->getSize()*/ 32 * 6, "1920 X 1080", 1.0f, 1.0f, 1.0f);
		GFX::drawString(0, 32 * 8, "VSYNC", 1.0f, 1.0f, 1.0f);
		if (vsync)
		{
			GFX::drawRect(128, 64, 128, 32 * 7, _menuTextures->getEnabledSecondTexture());
		}
		else
		{
			GFX::drawRect(128, 64, 128, 32 * 7, _menuTextures->getEnabledFirstTexture());
		}
		GFX::drawString(0, 32 * 10, "MSAA", 1.0f, 1.0f, 1.0f);
		if (msaa)
		{
			GFX::drawRect(128, 64, 128, 32 * 9, _menuTextures->getEnabledSecondTexture());
		}
		else
		{
			GFX::drawRect(128, 64, 128, 32 * 9, _menuTextures->getEnabledFirstTexture());
		}
	}
	else if (state == PAUSE_MENU)
	{
		int textureWidth = 256;
		int textureHeight = 64;
		if (_width == 1920)
		{
			textureWidth = 512;
		}
		if (_height == 1080)
		{
			textureHeight = 128;
		}

		resumeButton->draw();
		optionsPauseMenu->draw();
		exitPauseMenu->draw();
	}
	else if (state == LOADING)
	{
		std::string str = "";
		char loading[64] = "Loading...";
		//for (int i = 0; i < 10; i++)
		{
			//str += loading[i];
			GFX::drawString(_width / 2 - 32, _height / 2 - 32, loading, 1.0f, 1.0f, 1.0f);
			//std::this_thread::sleep_for(std::chrono::seconds(1));
		}
	}
}



bool checklist(std::vector<Vector2f*>* list, Vector2f v)
{
	for (int i = 0; i < list->size(); i++)
	{
		if (v.x == list->at(i)->x && v.y == list->at(i)->y)
		{
			return true;
		}
	}
	return false;
}

Game::~Game()
{
	delete _textures;
	delete _tiles;
	delete _units;
	delete _buildings;
	delete _selectedUnits;
	delete _camera;
	_input->destroyInput();
}

