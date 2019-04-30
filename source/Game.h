#pragma once
#include "Base.h"
#include "World.h"
#include "Menu.h"

class Game{
public:
	int runningRefresh;
	bool playing = false;
	bool roundFinished = false;
	bool restart = true;
	bool gameFinished = false;
	unsigned int frame = 0;
	unsigned int state = 0;
	unsigned int difficulty = 2;
	unsigned int time = 0;
	unsigned int prevTime = 0;
	unsigned int climbedSteps = 0;
	unsigned int bestScore[3] = {0, 0, 0};
	std::string difficultyStr;
	std::vector<int> stairsArray;
	std::unique_ptr<World> world;
	std::unique_ptr<Menu> menu;

	Game(int rows, int columns);
	void update();
	void draw();
	int getInput();
	void getMenuInput();
	~Game();
};

