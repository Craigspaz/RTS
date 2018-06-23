#include "MenuTextures.h"


MenuTextures::MenuTextures()
{
exitFirst = new Texture("res/Buttons/Exit_First.png");
exitSecond = new Texture("res/Buttons/Exit_Second.png");
pauseFirst = new Texture("res/Buttons/Pause.png");
pauseSecond = new Texture("res/Buttons/Pause1.png");
play = new Texture("res/Buttons/Play.png");
playFirst = new Texture("res/Buttons/Play_First.png");
playSecond = new Texture("res/Buttons/Play_Second.png");
play1 = new Texture("res/Buttons/Play1.png");
resumeFirst = new Texture("res/Buttons/Resume_First.png");
resumeSecond = new Texture("res/Buttons/Resume_Second.png");
backgroundTestTexture = new Texture("res/background.png");
settings = new Texture("res/settings.png");
highScores_first = new Texture("res/Buttons/HighScores_First.png");
highScores_second = new Texture("res/Buttons/HighScores_Second.png");
cursor = new Texture("res/cursor.png");
options_first = new Texture("res/Buttons/Options_First.png");
options_second = new Texture("res/Buttons/Options_Second.png");
enabled_first = new Texture("res/Buttons/Enabled.png");
enabled_second = new Texture("res/Buttons/Enabled_Second.png");
betterGrass = new Texture("res/betterGrass.png");
dirt = new Texture("res/dirt.png");
water = new Texture("res/water.png");
mountain = new Texture("res/mountain.png");
}


MenuTextures::~MenuTextures()
{
	delete exitFirst;
	delete exitSecond;
	delete pauseFirst;
	delete pauseSecond;
	delete playFirst;
	delete playSecond;
	delete play;
	delete play1;
	delete resumeFirst;
	delete resumeSecond;
	delete backgroundTestTexture;
	delete settings;
	delete highScores_first;
	delete highScores_second;
	delete cursor;
	delete options_first;
	delete options_second;
	delete enabled_first;
	delete enabled_second;
	delete betterGrass;
	delete dirt;
	delete water;
	delete mountain;
}



Texture* MenuTextures::getWaterTexture()
{
	return water;
}
Texture* MenuTextures::getMountainTexture()
{
	return mountain;
}
Texture* MenuTextures::getDirtTexture()
{
	return dirt;
}

Texture* MenuTextures::getBetterGrassTexture()
{
	return betterGrass;
}

Texture* MenuTextures::getBackgroundTestTexture()
{
	return backgroundTestTexture;
}
Texture* MenuTextures::getExitFirstTexture()
{
	return exitFirst;
}
Texture* MenuTextures::getExitSecondTexture()
{
	return exitSecond;
}
Texture* MenuTextures::getPauseFirstTexture()
{
	return pauseFirst;
}
Texture* MenuTextures::getPauseSecondTexture()
{
	return pauseSecond;
}
Texture* MenuTextures::getPlayFirstTexture()
{
	return playFirst;
}
Texture* MenuTextures::getPlaySecondTexture()
{
	return playSecond;
}
Texture* MenuTextures::getPlayTexture()
{
	return play;
}
Texture* MenuTextures::getPlay1Texture()
{
	return play1;
}
Texture* MenuTextures::getResumeFirstTexture()
{
	return resumeFirst;
}
Texture* MenuTextures::getResumeSecondTexture()
{
	return resumeSecond;
}
Texture* MenuTextures::getSettings()
{
	return settings;
}
Texture* MenuTextures::getHighScoreFirst()
{
	return highScores_first;
}
Texture* MenuTextures::getHighScoreSecond()
{
	return highScores_second;
}

Texture* MenuTextures::getCursorTexture()
{
	return cursor;
}
Texture* MenuTextures::getOptionsFirstTexture()
{
	return options_first;
}
Texture* MenuTextures::getOptionsSecondTexture()
{
	return options_second;
}
Texture* MenuTextures::getEnabledFirstTexture()
{
	return enabled_first;
}
Texture* MenuTextures::getEnabledSecondTexture()
{
	return enabled_second;
}