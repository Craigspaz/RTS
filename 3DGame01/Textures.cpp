#include "Textures.h"


Textures::Textures()
{
	air = new Texture("res/air.png");
	dirt = new Texture("res/dirt.png");
	dirt2 = new Texture("res/Dirt (2).png");
	laser = new Texture("res/Laser.png");
	enemy1 = new Texture("res/Enemy/Enemy1.png");
	enemy2 = new Texture("res/Enemy/Enemy2.png");
	enemy3 = new Texture("res/Enemy/Enemy3.png");
	enemy4 = new Texture("res/Enemy/Enemy4.png");
	enemy5 = new Texture("res/Enemy/Enemy5.png");
	enemy6 = new Texture("res/Enemy/Enemy6.png");
	enemy7 = new Texture("res/Enemy/Enemy7.png");
	enemy8 = new Texture("res/Enemy/Enemy8.png");
	back = new Texture("res/back.png");
	front = new Texture("res/front.png");
	left = new Texture("res/left.png");
	right = new Texture("res/right.png");
	bullet = new Texture("res/bullet.png");
	ammo = new Texture("res/ammo.png");
	armor = new Texture("res/armor.png");
	grassTop = new Texture("res/grassTop.png");
	grass = new Texture("res/grass.png");
	mountain = new Texture("res/mountain.png");
	water = new Texture("res/water.png");
	tank_right = new Texture("res/units/tank_right.png");
	tank_left = new Texture("res/units/tank_left.png");
	tank_up = new Texture("res/units/tank_up.png");
	tank_down = new Texture("res/units/tank_down.png");
	tank_down_left = new Texture("res/units/tank_diagnal_down_left.png");
	tank_down_right = new Texture("res/units/tank_diagnal_down_right.png");
	tank_up_left = new Texture("res/units/tank_diagnal_up_left.png");
	tank_up_right = new Texture("res/units/tank_diagnal_up_right.png");
	soldier_down = new Texture("res/units/soldier_down.png");
	soldier_up = new Texture("res/units/soldier_up.png");
	soldier_right = new Texture("res/units/soldier_right.png");
	soldier_left = new Texture("res/units/soldier_left.png");
	building_barracks = new Texture("res/buildings/building_barracks.png");
	building_factory = new Texture("res/buildings/building_factory.png");
	controls_background = new Texture("res/controls_background.png");
	selectionbox = new Texture("res/selectionsbox.png");
	map01 = new Texture("res/minimap03.png");
	generatedMap = new Texture("res/generatedMap.png");
	hover = new Texture("res/hover.png");
	minimapsquare = new Texture("res/mapCameraView.png");
	betterGrass = new Texture("res/betterGrass.png");
	greenHealth = new Texture("res/greenHealth.png");
	redHealth = new Texture("res/redHealth.png");
	yellowHealth = new Texture("res/yellowHealth.png");
	stopTexture = new Texture("res/stopImage.png");
	greenHover = new Texture("res/greenHover.png");
	redHover = new Texture("res/redHover.png");
	building0Percent = new Texture("res/building_cover/0percent.png");
	building10Percent = new Texture("res/building_cover/10percent.png");
	building20Percent = new Texture("res/building_cover/20percent.png");
	building30Percent = new Texture("res/building_cover/30percent.png");
	building40Percent = new Texture("res/building_cover/40percent.png");
	building50Percent = new Texture("res/building_cover/50percent.png");
	building60Percent = new Texture("res/building_cover/60percent.png");
	building70Percent = new Texture("res/building_cover/70percent.png");
	building80Percent = new Texture("res/building_cover/80percent.png");
	building90Percent = new Texture("res/building_cover/90percent.png");
	building100Percent = new Texture("res/building_cover/100percent.png");
	bridge = new Texture("res/bridge.png");
	tankShell = new Texture("res/Ammunition/Tank_Shell.png");
	soldierBullet = new Texture("res/Ammunition/Soldier_Shell.png");
}


Textures::~Textures()
{
	delete air;
	delete dirt2;
	delete dirt;
	delete laser;
	delete enemy1;
	delete enemy2;
	delete enemy3;
	delete enemy4;
	delete enemy5;
	delete enemy6;
	delete enemy7;
	delete enemy8;
	delete back;
	delete front;
	delete left;
	delete right;
	delete bullet;
	delete ammo;
	delete armor;
	delete grassTop;
	delete grass;
	delete mountain;
	delete water;
	delete tank_right;
	delete tank_left;
	delete tank_up;
	delete tank_down;
	delete tank_down_right;
	delete tank_down_left;
	delete tank_up_left;
	delete tank_up_right;
	delete soldier_down;
	delete soldier_up;
	delete soldier_right;
	delete soldier_left;
	delete building_factory;
	delete building_barracks;
	delete controls_background;
	delete selectionbox;
	delete map01;
	delete hover;
	delete minimapsquare;
	delete betterGrass;
	delete yellowHealth;
	delete redHealth;
	delete greenHealth;
	delete stopTexture;
	delete greenHover;
	delete redHover;
	delete building0Percent;
	delete building10Percent;
	delete building20Percent;
	delete building30Percent;
	delete building40Percent;
	delete building50Percent;
	delete building60Percent;
	delete building70Percent;
	delete building80Percent;
	delete building90Percent;
	delete building100Percent;
	delete generatedMap;
	delete bridge;
	delete tankShell;
	delete soldierBullet;
}


Texture* Textures::getAirTexture()
{
	return air;
}
Texture* Textures::getDirt2Texture()
{
	return dirt2;
}
Texture* Textures::getDirtTexture()
{
	return dirt;
}
Texture* Textures::getLaserTexture()
{
	return laser;
}
Texture* Textures::getEnemy1Texture()
{
	return enemy1;
}
Texture* Textures::getEnemy2Texture()
{
	return enemy2;
}
Texture* Textures::getEnemy3Texture()
{
	return enemy3;
}
Texture* Textures::getEnemy4Texture()
{
	return enemy4;
}
Texture* Textures::getEnemy5Texture()
{
	return enemy4;
}
Texture* Textures::getEnemy6Texture()
{
	return enemy6;
}
Texture* Textures::getEnemy7Texture()
{
	return enemy7;
}
Texture* Textures::getEnemy8Texture()
{
	return enemy8;
}
Texture* Textures::getPlayerFrontTexture()
{
	return front;
}
Texture* Textures::getPlayerBackTexture()
{
	return back;
}
Texture* Textures::getPlayerLeftTexture()
{
	return left;
}
Texture* Textures::getPlayerRightTexture()
{
	return right;
}
Texture* Textures::getBulletTexture()
{
	return bullet;
}
Texture* Textures::getAmmoTexture()
{
	return ammo;
}
Texture* Textures::getArmorTexture()
{
	return armor;
}


Texture* Textures::getGrassTopTexture()
{
	return grassTop;
}
Texture* Textures::getGrassTexture()
{
	return grass;
}


Texture* Textures::getMountainTexture()
{
	return mountain;
}


Texture* Textures::getWaterTexture()
{
	return water;
}


Texture* Textures::getTankRightTexture()
{
	return tank_right;
}
Texture* Textures::getTankDownTexture()
{
	return tank_down;
}
Texture* Textures::getTankUpTexture()
{
	return tank_up;
}
Texture* Textures::getTankLeftTexture()
{
	return tank_left;
}
Texture* Textures::getSoldierDownTexture()
{
	return soldier_down;
}
Texture* Textures::getSoldierUpTexture()
{
	return soldier_up;;
}
Texture* Textures::getSoldierLeftTexture()
{
	return soldier_left;
}
Texture* Textures::getSoldierRightTexture()
{
	return soldier_right;
}

Texture* Textures::getTankDownLeftTexture()
{
	return tank_down_left;
}

Texture* Textures::getTankDownRightTexture()
{
	return tank_down_right;
}

Texture* Textures::getTankUpRightTexture()
{
	return tank_up_right;
}

Texture* Textures::getTankUpLeftTexture()
{
	return tank_up_left;
}


Texture* Textures::getBuildingFactoryTexture()
{
	return building_factory;
}
Texture* Textures::getBuildingBarracksTexture()
{
	return building_barracks;
}


Texture* Textures::getControlsBackground()
{
	return controls_background;
}
Texture* Textures::getSelectionBox()
{
	return selectionbox;
}
Texture* Textures::getMap01IMGTexture()
{
	return map01;
}

Texture* Textures::getHoverTexture()
{
	return hover;
}

Texture* Textures::getMinimapSquare()
{
	return minimapsquare;
}

Texture* Textures::getBetterGrassTexture()
{
	return betterGrass;
}

Texture* Textures::getGreenHealthTexture()
{
	return greenHealth;
}

Texture* Textures::getYellowHealthTexture()
{
	return yellowHealth;
}

Texture* Textures::getRedHealthTexture()
{
	return redHealth;
}

Texture* Textures::getStopTexture()
{
	return stopTexture;
}

Texture* Textures::getGreenHoverTexture()
{
	return greenHover;
}

Texture* Textures::getRedHoverTexture()
{
	return redHover;
}

Texture* Textures::getBuilding0Percent()
{
	return building0Percent;
}
Texture* Textures::getBuilding10Percent()
{
	return building10Percent;
}
Texture* Textures::getBuilding20Percent()
{
	return building20Percent;
}
Texture* Textures::getBuilding30Percent()
{
	return building30Percent;
}
Texture* Textures::getBuilding40Percent()
{
	return building40Percent;
}
Texture* Textures::getBuilding50Percent()
{
	return building50Percent;
}
Texture* Textures::getBuilding60Percent()
{
	return building60Percent;
}
Texture* Textures::getBuilding70Percent()
{
	return building70Percent;
}
Texture* Textures::getBuilding80Percent()
{
	return building80Percent;
}
Texture* Textures::getBuilding90Percent()
{
	return building90Percent;
}
Texture* Textures::getBuilding100Percent()
{
	return building100Percent;
}
Texture* Textures::getGeneratedMap()
{
	return generatedMap;
}

Texture* Textures::getBridgeTexture()
{
	return bridge;
}


Texture* Textures::getTankShell()
{
	return tankShell;
}
Texture* Textures::getSoldierBullet()
{
	return soldierBullet;
}