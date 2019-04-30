#include "Stairs.h"
#include "World.h"

Stairs::Stairs(World* w, int x, int y, int s){
	world = w;

	// Stairs variables
	size = s;
	sink = 0;
	if (world->rows - (world->rows - y) < size + 1) { size = world->rows - (world->rows - y) - 1; }
	startPosition.set(x, y);
	endPosition.set(x + size * 2, y - size);
	
	// Sort variables
	for (int i = 0; i < size; i++) stepArray.push_back(i+1);
	std::random_shuffle(stepArray.begin(), stepArray.end());
	
	sortIndex = 1;
	secondSorterIndex = -1;
	sorting = false;
	sorted = false;
}

void Stairs::moveLeft() {
	startPosition.x -= 2;
	endPosition.x -= 2;
}

void Stairs::moveDown(){	
	sink += 1;
}

void Stairs::activateSorter(std::shared_ptr<Sorter> _sorter) {
	sorter = _sorter;
	sorter->activate(&stepArray, &sortIndex, &secondSorterIndex);
}

void Stairs::sort(){

	//Check if sorted
	sorted = true;
	sorting = false;
	for (int i = 1; i < stepArray.size(); i++) {
		if (stepArray[i - 1] > stepArray[i]) {
			sorted = false;
			sorting = true;
			break;
		}
	}
	// Sort the stairs if the pointer to sorter isnt null and stairs arent sorted
	if (sorter && !sorted) {
		sorting = true;
		sorter->sort();
	}
}

void Stairs::draw(){
		int x = min(max(startPosition.x, world->runnerPosition), world->columns - 1);
		int y = startPosition.y;
		int endx = min(max(endPosition.x, world->runnerPosition), world->columns - 1);
		int endy = endPosition.y;		
		
		int firstStep = abs(min(startPosition.x, world->runnerPosition) - world->runnerPosition)/2;
		int lastStep = stepArray.size() - max(0, floor((float)(endPosition.x - world->columns)) / 2);

		// Draw stairs
		std::vector<int> steps;
		for (int i = firstStep; i < lastStep; i++){
			steps.push_back(max(stepArray[i] - sink, 0));
		}	
		drawSteps(x, y, endx, endy, steps);

		// Draw info and other stuff
		std::ostringstream stream;
		stream << "Size: " << size << " steps";
		int streamLength = stream.str().length();
		int spaceForString = world->columns - (startPosition.x + size);

		if (!sorted && !sorting && spaceForString > streamLength/2) {
			drawCenterString(startPosition.x + size, y + 1, stream.str());
		}
		if (sorting && !sorted) {
			drawString(x + (sortIndex) * 2 + 1, y + 1, "^");
			if(secondSorterIndex >= 0) drawString(x + (secondSorterIndex) * 2 + 1, y + 1, "\304");
		}
}

void Stairs::clear() {
	clearBlock(max(startPosition.x - 1, 0), startPosition.y + 3, min(endPosition.x, world->columns), endPosition.y);
}

Stairs::~Stairs() {
	clear();
}
