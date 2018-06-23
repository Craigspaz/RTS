#ifndef _PLAYER_H
#define _PLAYER_H
/*The Player class*/
class Player
{
public:
	Player(int money, bool AI, int playerNumber, char* playerName,int faction);
	~Player();
	int getMoney();
	void setMoney(int money);
	bool getAI();
	void setAI(bool a);
	int getPlayerNumber();
	void setPlayerNumber(int playerNumber);
	char* getPlayerName();
	void setPlayerName(char* playername);
	void setFaction(int faction);
	int getFaction();
private:
	int _money;
	bool _AI;
	int _playerNumber;
	char* _playername;
	int _faction;
};

#endif