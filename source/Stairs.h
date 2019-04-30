class World;
#pragma once
#include"Base.h"
#include "Sorter.h"

class Stairs{
public:
	World* world;
	int size;
	int sink;
	Vector2D startPosition;
	Vector2D endPosition;

	std::vector<int> stepArray;
	std::vector<int> activeSteps;
	std::shared_ptr<Sorter> sorter;
	int sortIndex;
	int secondSorterIndex;
	bool sorting;
	bool sorted;


	Stairs(World* w, int x, int y, int s);
	void moveLeft();
	void moveDown();
	void activateSorter(std::shared_ptr<Sorter> _sorter);
	void sort();
	void draw();
	void clear();
	~Stairs();

private:

	
};

