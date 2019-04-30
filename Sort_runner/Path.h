class World;
#pragma once
#include"Base.h"

class Path{
public:
	World* world;
	Vector2D startPosition;
	Vector2D endPosition;

	Path(World* w, int x, int y, int endx, int endy);
	void moveLeft();
	void moveDown();
	void draw();
	void clear();
	~Path();
};

