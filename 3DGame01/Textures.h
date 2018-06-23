#ifndef _TEXTURES_H
#define _TEXTURES_H
#include <iostream>
#include "Texture.h"
/*This class stores all of the loaded textures for easy access*/
class Textures
{
public:
	Textures();
	~Textures();
	Texture* getAirTexture();
	Texture* getDirt2Texture();
	Texture* getDirtTexture();
	Texture* getLaserTexture();
	Texture* getEnemy1Texture();
	Texture* getEnemy2Texture();
	Texture* getEnemy3Texture();
	Texture* getEnemy4Texture();
	Texture* getEnemy5Texture();
	Texture* getEnemy6Texture();
	Texture* getEnemy7Texture();
	Texture* getEnemy8Texture();
	Texture* getPlayerFrontTexture();
	Texture* getPlayerBackTexture();
	Texture* getPlayerLeftTexture();
	Texture* getPlayerRightTexture();
	Texture* getBulletTexture();
	Texture* getAmmoTexture();
	Texture* getArmorTexture();
	Texture* getGrassTopTexture();
	Texture* getGrassTexture();
	Texture* getMountainTexture();
	Texture* getWaterTexture();
	Texture* getTankRightTexture();
	Texture* getTankUpTexture();
	Texture* getTankLeftTexture();
	Texture* getTankDownTexture();
	Texture* getTankUpLeftTexture();
	Texture* getTankUpRightTexture();
	Texture* getTankDownLeftTexture();
	Texture* getTankDownRightTexture();
	Texture* getSoldierDownTexture();
	Texture* getSoldierUpTexture();
	Texture* getSoldierLeftTexture();
	Texture* getSoldierRightTexture();

	Texture* getBuildingFactoryTexture();
	Texture* getBuildingBarracksTexture();

	Texture* getControlsBackground();
	Texture* getSelectionBox();
	Texture* getMap01IMGTexture();

	Texture* getHoverTexture();
	Texture* getMinimapSquare();
	Texture* getBetterGrassTexture();
	
	Texture* getGreenHealthTexture();
	Texture* getYellowHealthTexture();
	Texture* getRedHealthTexture();

	Texture* getStopTexture();

	Texture* getRedHoverTexture();
	Texture* getGreenHoverTexture();

	Texture* getBuilding0Percent();
	Texture* getBuilding10Percent();
	Texture* getBuilding20Percent();
	Texture* getBuilding30Percent();
	Texture* getBuilding40Percent();
	Texture* getBuilding50Percent();
	Texture* getBuilding60Percent();
	Texture* getBuilding70Percent();
	Texture* getBuilding80Percent();
	Texture* getBuilding90Percent();
	Texture* getBuilding100Percent();
	Texture* getGeneratedMap();
	Texture* getBridgeTexture();
	Texture* getTankShell();
	Texture* getSoldierBullet();
private:
	Texture* air;
	Texture* dirt2;
	Texture* dirt;
	Texture* laser;
	Texture* enemy1;
	Texture* enemy2;
	Texture* enemy3;
	Texture* enemy4;
	Texture* enemy5;
	Texture* enemy6;
	Texture* enemy7;
	Texture* enemy8;
	Texture* back;
	Texture* front;
	Texture* left;
	Texture* right;
	Texture* bullet;
	Texture* ammo;
	Texture* armor;
	Texture* grass;
	Texture* grassTop;
	Texture* mountain;
	Texture* water;
	Texture* controls_background;
	Texture* betterGrass;
	Texture* bridge;

	//Tank
	Texture* tank_right;
	Texture* tank_left; 
	Texture* tank_up;
	Texture* tank_down;
	Texture* tank_up_left;
	Texture* tank_up_right;
	Texture* tank_down_right;
	Texture* tank_down_left;

	//Soldier
	Texture* soldier_right;
	Texture* soldier_left;
	Texture* soldier_up;
	Texture* soldier_down;

	//Buildings
	Texture* building_factory;
	Texture* building_barracks;

	Texture* selectionbox;

	//Maps
	Texture* map01;

	Texture* generatedMap;

	Texture* hover;
	Texture* minimapsquare;

	Texture* greenHealth;
	Texture* yellowHealth;
	Texture* redHealth;

	Texture* stopTexture;

	Texture* greenHover;
	Texture* redHover;

	Texture* building0Percent;
	Texture* building10Percent;
	Texture* building20Percent;
	Texture* building30Percent;
	Texture* building40Percent;
	Texture* building50Percent;
	Texture* building60Percent;
	Texture* building70Percent;
	Texture* building80Percent;
	Texture* building90Percent;
	Texture* building100Percent;

	Texture* soldierBullet;
	Texture* tankShell;
};

#endif