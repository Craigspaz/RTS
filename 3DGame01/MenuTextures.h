#ifndef _MENU_TEXTURES
#define _MENU_TEXTURES
#include "Texture.h"
/*Loads textures used by the menu and makes getters to retrieve them*/
class MenuTextures
{
public:
	MenuTextures();
	~MenuTextures(); 
	Texture* getBackgroundTestTexture();
	Texture* getExitFirstTexture();
	Texture* getExitSecondTexture();
	Texture* getPauseFirstTexture();
	Texture* getPauseSecondTexture();
	Texture* getPlayFirstTexture();
	Texture* getPlaySecondTexture();
	Texture* getPlayTexture();
	Texture* getPlay1Texture();
	Texture* getResumeFirstTexture();
	Texture* getResumeSecondTexture();
	Texture* getSettings();
	Texture* getHighScoreFirst();
	Texture* getHighScoreSecond();
	Texture* getCursorTexture();
	Texture* getOptionsFirstTexture();
	Texture* getOptionsSecondTexture();
	Texture* getEnabledFirstTexture();
	Texture* getEnabledSecondTexture();
	Texture* getBetterGrassTexture();
	Texture* getDirtTexture();
	Texture* getWaterTexture();
	Texture* getMountainTexture();


private:
	Texture* dirt;
	Texture* exitFirst;
	Texture* exitSecond;
	Texture* pauseFirst;
	Texture* pauseSecond;
	Texture* playFirst;
	Texture* playSecond;
	Texture* play;
	Texture* play1;
	Texture* resumeFirst;
	Texture* resumeSecond;
	Texture* settings;
	Texture* backgroundTestTexture;
	Texture* highScores_first;
	Texture* highScores_second;
	Texture* cursor;
	Texture* options_first;
	Texture* options_second;
	Texture* enabled_first;
	Texture* enabled_second;
	Texture* betterGrass;
	Texture* water;
	Texture* mountain;
};

#endif