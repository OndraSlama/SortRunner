#include "World.h"
#include "Game.h"


World::World(Game* _game,int _rows, int _cols) {
	game = _game;
	columns = _cols;
	rows = _rows;
	ground = rows - 10;
	runnerPosition = 6;
	stairsStop = 10;
	gatePosition = columns - 6;
}

void World::addStairs(float relativeX, int size){
	int x = (float)columns * relativeX;
	stairs.reset(new Stairs(this, x, ground, size));
	lowerPath.reset(new Path(this, 0, ground, x - 1, ground));
	higherPath.reset(new Path(this, stairs->endPosition.x, stairs->endPosition.y, columns, stairs->endPosition.y));
}

void World::moveLeft(){	// moves the stairs left
	stairs->moveLeft();
	lowerPath->moveLeft();
	higherPath->moveLeft();
	if (game->roundFinished) {
		gatePosition--;
	}
}

void World::moveDown() { 	// moves the stairs down
	stairs->moveDown();
	lowerPath->moveDown();
	higherPath->moveDown();
}

void World::draw(){	
	lowerPath->draw();
	higherPath->draw();
	stairs->draw();		

	if (gatePosition > runnerPosition) {
		drawStickman(runnerPosition, ground);
	} else {
		drawHappyStickman(runnerPosition, ground);
	}

	if (game->roundFinished) {
		drawHeaven(gatePosition, ground);
	}
}

void World::clear() {

	if (stairs->sorting) {
		fillSection(ground + 2, ground, columns, ' '); // to eliminate blinking when sorting, clear only one line below ground
	} else {
		fillSection(ground + 2, 0, columns, ' '); // clear the whole screen
	}
}

World::~World(){

}
