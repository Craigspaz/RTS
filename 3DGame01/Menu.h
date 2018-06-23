#ifndef _MENU_H
#define _MENU_H
class Menu
{
public:
	Menu();
	virtual void update() = 0;
	virtual void render() = 0;
	~Menu();
};

#endif