#include "Player.h"

Player::Player(int money, bool AI, int playerNumber, char* playerName, int faction) :
_money(money),
_AI(AI),
_playerNumber(playerNumber),
_playername(playerName),
_faction(faction)
{

}
Player::~Player()
{

}
int Player::getMoney()
{
	return _money;
}
void Player::setMoney(int money)
{
	_money = money;
}
bool Player::getAI()
{
	return _AI;
}
void Player::setAI(bool a)
{
	_AI = a;
}
int Player::getPlayerNumber()
{
	return _playerNumber;
}
void Player::setPlayerNumber(int playerNumber)
{
	_playerNumber = playerNumber;
}
char* Player::getPlayerName()
{
	return _playername;
}
void Player::setPlayerName(char* playername)
{
	_playername = playername;
}


void Player::setFaction(int faction)
{
	_faction = faction;
}
int Player::getFaction()
{
	return _faction;
}