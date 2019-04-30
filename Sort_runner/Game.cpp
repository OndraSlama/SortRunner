#include "Game.h"
#include "Sorter.h"
#include <conio.h>


#define START_SCREEN 0
#define GAME_START 1
#define STAIRS_NOWHERE_NEAR 10
#define STAIRS_INFRONT 20
#define STAIRS_SORTED 30
#define STAIRS_BEHIND 40
#define FINAL_RUN 50
#define END 99

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

Game::Game(int rows, int columns){
	//Create unique pointer
	world = std::make_unique<World>(this, rows, columns);
	menu = std::make_unique<Menu>(world.get());
	
	// Determine how often will the world update bedore being drawn on screen (when closing on stairs)
	runningRefresh = 8;
	
}

void Game::update(){ // Main logic of the game

	frame++;	
	int c;
	
	// States of the game
	switch (state) {
	
	case START_SCREEN: // Before the game starts
		int xPos;
		int yPos;
		xPos = world->columns / 2;
		yPos = world->rows / 2 - 5;

		//Draw Introduction info
		fillSection(world->rows, 0, world->columns, ' ');
		drawCenterString(xPos, yPos - 1, "SORT RUNNER");
		drawCenterString(xPos, yPos + 1, "Your main objective in this game will be very simple.");
		drawCenterString(xPos, yPos + 2, "You will need to sort your stairway to heaven.");
		drawCenterString(xPos, yPos + 3, "The better sorting algorithm used on each stairs you encounter, the faster sorting time and thus better score.");
		drawCenterString(xPos, yPos + 4, "But here is the catch. You don't have unlimited number of every available sorting algorithm.");
		drawCenterString(xPos, yPos + 5, "You will need to think about when and why to use one.");
		drawCenterString(xPos, yPos + 6, "Good Luck!");
		drawCenterString(xPos, yPos + 8, "-Select difficulty-");

		//Draw difficulty selection
		int diffPos[3];
		diffPos[0] = xPos - 11;
		diffPos[1] = xPos - 3;
		diffPos[2] = xPos + 7;
		
		drawString(diffPos[0], yPos + 10, "Easy");
		drawString(diffPos[1], yPos + 10, "Medium");
		drawString(diffPos[2], yPos + 10, "Hard");

		drawString(diffPos[difficulty - 1] - 1, yPos + 10, "\257");	

		//Handle difficulty selection	  
		c = getInput();

		if (c == KEY_LEFT) {
			if (--difficulty < 1) difficulty = 3;
		} else if (c == KEY_RIGHT) {
			if (++difficulty > 3) difficulty = 1;
		}else if (c == ENTER) {
			state = GAME_START;
		}
		
		break;

	case GAME_START: // Here, all the preparation for the game occurs (creates items in invetory, sets up stairs etc.)

		// Reset score
		time = 0;

		// Create round based on selected difficulty
		switch (difficulty) {
		case 1:
			difficultyStr = "easy";
			stairsArray.insert(stairsArray.end(), {12, 20, 8, 16});
			menu->addSorter(std::make_unique<ShakerSort>(), 1);
			menu->addSorter(std::make_unique<OptimizedShakerSort>(), 1);
			menu->addSorter(std::make_unique<SelectionSort>(), 1);
			menu->addSorter(std::make_unique<BubbleSort>(), 2);
			break;

		case 2:
			difficultyStr = "medium";
			stairsArray.insert(stairsArray.end(), { 7, 13, 26, 4, 10, 23});
			menu->addSorter(std::make_unique<BogoSort>(), 1);
			menu->addSorter(std::make_unique<ShakerSort>(), 1);
			menu->addSorter(std::make_unique<SelectionSort>(), 1);
			menu->addSorter(std::make_unique<InsertionSort>(), 2);
			menu->addSorter(std::make_unique<OptimizedBubbleSort>(), 2);
			break;

		case 3:
			difficultyStr = "hard";
			stairsArray.insert(stairsArray.end(), { 16, 25, 30, 13, 9, 40, 3, 2, 10, 25});
			menu->addSorter(std::make_unique<BogoSort>(), 2);
			menu->addSorter(std::make_unique<BubbleSort>(), 3);
			menu->addSorter(std::make_unique<InsertionSort>(), 2);
			menu->addSorter(std::make_unique<QuickSort>(), 2);
			menu->addSorter(std::make_unique<OptimizedBubbleSort>(), 1);
			break;

		default:
			break;
		}

		//Add first stairs to the world
		world->addStairs(1, stairsArray.front());
		stairsArray.erase(stairsArray.begin());

		//Wait for user input
		menu->showMessage("Are you ready? Press any key to start the game...");
		world->clear();
		world->draw();
		c = getInput();
		
		// First message
		if (world->stairs) {
			menu->showMessage("BEWARE!");
			state = STAIRS_NOWHERE_NEAR;
			playing = true;
		}
		break;

	case STAIRS_NOWHERE_NEAR: // Before stairs infront -> running to them
		world->moveLeft();
		int trigger;
		trigger = round(world->columns*0.6);
		if (world->stairs->startPosition.x < trigger && world->stairs->startPosition.x > trigger - 4) {
			
			if (climbedSteps == 0) {
				menu->showMessage("A wild unsorted stairs appear!");
			} else {
				menu->showMessage("OH NO!, another wild unsorted stairs appear!");
			}
		}
		if (world->stairs->startPosition.x <= world->stairsStop) {
			state = STAIRS_INFRONT;	
			world->clear();
			world->draw();
		}
		break;

	case STAIRS_INFRONT: // Stairs are infront of the runner -> selection of algorithm and sorting
		if (!world->stairs->sorter) {
			menu->showMessage("Select sorting algorithm. Think carefully!");
			menu->processInput(getInput());
			prevTime = time;
			menu->showMessage("Stairs are being sorted.");
		} else {
			if (!world->stairs->sorted) {
				world->stairs->sort();
				time++;
				if (time - prevTime == 700) {
					menu->showMessage("Seems like you have chosen badly :/.");
				}
				if (time - prevTime == 1200) {
					menu->showMessage("Ok, thats enough. Lets just use a better one for free this time.");
					world->stairs->activateSorter(std::make_shared<QuickSort>());
				}
			} else {
				state = STAIRS_SORTED;
				std::ostringstream stream;
				stream << "Well done. Stairs sorted in " << time - prevTime << " cycles.";
				menu->showMessage(stream.str());
			}
		}
		break;

	case STAIRS_SORTED: // Stairs sorted -> climbing
		if (world->higherPath->endPosition.y < world->ground) {
			world->moveDown();
			climbedSteps++;
		}
		world->moveLeft();

		if (world->higherPath->endPosition.y == world->ground && world->stairs->endPosition.x < 0) {
			state = STAIRS_BEHIND;
		}
		break;

	case STAIRS_BEHIND: // Stairs behind runner -> creating new stairs or finnishing the round
		if (stairsArray.size() > 0) {
			world->addStairs(1, stairsArray.front());
			stairsArray.erase(stairsArray.begin());
			state = STAIRS_NOWHERE_NEAR;
			menu->showMessage("One stairway closer to heaven.");
		} else {
			roundFinished = true;
			state = FINAL_RUN;
			menu->showMessage("No way, I can finally see the heaven gate!");
		}
		break;

	case FINAL_RUN: // Final run to the heaven gate
		world->moveLeft();

		if (world->gatePosition == round(world->columns*0.7)) {
			menu->showMessage("Almost there!");
		}

		if (world->gatePosition == round(world->columns*0.5)) {
			menu->showMessage("Just a little bit further.");
		}

		if (world->gatePosition == round(world->columns*0.3)) {
			menu->showMessage("Taking a bit too long...");
		}

		if (world->gatePosition == 0) {
			state = END;
			menu->showMessage("Hello Heaven!");
			frame = 0;
			if (bestScore[difficulty - 1] > time || bestScore[difficulty - 1] == 0) {
				bestScore[difficulty - 1] = time;
			}

		}
		break;

	case END: // Ending screen with options to quit or restart the game
		playing = false;

		if (frame > 20) {
			world->clear();
			menu->clear();

			int xPos;
			int yPos;
			xPos = world->columns / 2;
			yPos = world->rows / 2;

			// Draw ending info
			std::ostringstream endInfo;
			endInfo << "You have finished the game in: " << time << " sorting cycles (the lower, the better).";

			drawCenterString(xPos, yPos - 4, "CONGRATULATIONS");
			drawCenterString(xPos, yPos - 2, endInfo.str());
			drawCenterString(xPos, yPos - 1, "You can try to lower that number with different combinations of used algorithms for the chosen difficulty");
		
			endInfo.str("");
			endInfo << "Your best score on " << difficultyStr << " difficulty is: " << bestScore[difficulty - 1] << " cycles.";

			drawCenterString(xPos, yPos + 1, endInfo.str());
			
			drawCenterString(xPos, yPos + 3, "So now, how would you like to proceed?");

			//Draw ending selection
			int endPos[2];
			endPos[0] = xPos - 13;
			endPos[1] = xPos + 4;

			drawString(endPos[0], yPos + 5, "Quit game");
			drawString(endPos[1], yPos + 5, "Restart game");
			drawString(endPos[restart] - 1, yPos + 5, "\257");

			//Handle ending selection	  
			c = getInput();

			if (c == KEY_LEFT || c == KEY_RIGHT) {
				restart = !restart;
			} else if (c == ENTER) {
				if (restart) {
					state = START_SCREEN;
					roundFinished = false;
					climbedSteps = 0;
					time = 0;
					world.reset(new World(this, world->rows, world->columns));
					menu.reset(new Menu(world.get()));
				} else {
					gameFinished = true;
				}
			}

		}
		break;

	default:
		break;
	}		
}

void Game::draw() { // Function for drawing the entire world (not menu!)
	if (playing) {
		if (state == STAIRS_INFRONT || state == STAIRS_SORTED || state == FINAL_RUN || frame % runningRefresh == 0) {
			world->clear();
			world->draw();
		}
	}
}

int Game::getInput() { // User input
	int c;
	c = _getch();
	if (c == 0 || c == 224) { // If arrows are pressed, two inputs are buffered. First 224 or 0 than arrow ID
		c = _getch();
		return c;
	} else {
		return c;
	}	
}


Game::~Game(){
}
