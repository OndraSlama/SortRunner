class Game;
#pragma once
#include "Base.h"
#include "Sorter.h"
#include "World.h"


class Algorithm
{
public:
	std::string name;
	int quantity;
	bool active = false;
	std::shared_ptr<Sorter> sorter;

	Algorithm(std::string _name, std::shared_ptr<Sorter> _sorter, int _quantity = 1);
};

class Menu
{
public:
	World* world;
	Game* game;
	int state = 10;
	Vector2D start;
	Vector2D end;
	int infoSectionStart;
	int quantitySectionStart;
	Algorithm* activeSorter;
	int activeSorterIndex = 0;	
	bool confirmation = true;
	std::vector<Algorithm> inventory;
	std::string message = "Hello World!";

	Menu(World* _world);
	void addSorter(std::shared_ptr<Sorter> _sorter, int _quantity);
	void processInput(int input);
	void selectSorter();
	void showMessage(std::string _message);
	void draw();
	void clear();
};



