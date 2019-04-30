class Game;
#pragma once
#include "Base.h"
#include "Stairs.h"
#include "Path.h"

class World
{
public:
	int columns;
	int rows;
	int ground;
	int runnerPosition;
	int stairsStop;
	int gatePosition;
	Game* game;
	std::unique_ptr<Stairs> stairs;
	std::unique_ptr<Path> lowerPath;
	std::unique_ptr<Path> higherPath;

	World(Game* game, int _rows, int _cols);
	void addStairs(float relativeX, int size);
	void moveLeft();
	void moveDown();
	void draw();
	void clear();

	~World();	
};
