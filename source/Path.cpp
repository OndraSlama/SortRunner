#include "Path.h"
#include "World.h"
//Path class

Path::Path(World* w, int x, int y, int endx, int endy){
	world = w;
	startPosition.set(x, y);
	endPosition.set(endx, endy);
}

void Path::moveLeft(){
	if(startPosition.x > 0)	startPosition.x -= 2;
	if(endPosition.x < world->columns) endPosition.x -= 2;
}

void Path::moveDown(){
	startPosition.y += 1;
	endPosition.y += 1;
}

void Path::draw(){
	int x = min(max(startPosition.x, 0), world->columns);
	int y = min(max(startPosition.y, 0), world->rows);
	int endx = min(max(endPosition.x, 0), world->columns);
	int endy = min(max(endPosition.y, 0), world->rows);
	if (startPosition.y <= world->ground) line(x, y, endx, endy);
}

void Path::clear(){
	int x = min(max(startPosition.x, 0), world->columns);
	int y = min(max(startPosition.y, 0), world->rows);
	int endx = min(max(endPosition.x, 0), world->columns);
	int endy = min(max(endPosition.y, 0), world->rows);

	clearLine(x, y, endx, endy);
}

Path::~Path(){
	clear();
}
