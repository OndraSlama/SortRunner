#include "Menu.h"
#include "Game.h"


#define INVENTORY 10
#define ITEM_CONFIRMATION 11
#define INVENTORY_EMPTY 12

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER 13

// Class for menu below the ground level of the world

Menu::Menu(World* _world) {
	world = _world;
	game = world->game;
	start.x = 0;
	start.y = world->rows - 1;
	end.x = world->columns-1;
	end.y = world->ground + 2;	
	infoSectionStart = start.x + 45;
	quantitySectionStart = start.x + 30;
}

void Menu::addSorter(std::shared_ptr<Sorter> _sorter, int _quantity) {
	inventory.push_back(Algorithm(_sorter->name, _sorter, _quantity));
	inventory[activeSorterIndex].active = true;
	activeSorter = &inventory[activeSorterIndex];
}

void Menu::processInput(int input) {
	// Main states of menu
	switch (state) {
	case INVENTORY: // Selection of algorithm
		if (inventory.size() <= 0) {
			state = INVENTORY_EMPTY;
			break;
		}

		if (input == KEY_UP) {
			if (++activeSorterIndex >= inventory.size()) activeSorterIndex = 0;
		} else if (input == KEY_DOWN) {
			if (--activeSorterIndex < 0) activeSorterIndex = inventory.size() - 1;
		} else if (input == ENTER) {
			if (activeSorter->quantity > 0) {
				state = ITEM_CONFIRMATION;
			}
		}
		break;

	case ITEM_CONFIRMATION: // Confim the selected item (algorithm)
		if (input == KEY_LEFT || input == KEY_RIGHT) {
			confirmation = !confirmation;
		} else if (input == ENTER) {
			if (confirmation) selectSorter();
			state = INVENTORY;
		}
		break;

	case INVENTORY_EMPTY:
		if (inventory.size() > 0) {
			state = INVENTORY;
			break;
		}
		break;

	default:
		break;
	}

	//Delete depleted algoritms
	for (int i = inventory.size() - 1; i >= 0; i--) {
		if (inventory[i].quantity <= 0) {
			inventory.erase(inventory.begin() + i);
			if (--activeSorterIndex < 0) activeSorterIndex = 0;
		}
	}

	//Set active sorter
	for (int i = 0; i < inventory.size(); i++) {
		inventory[i].active = false;
	}
	if (inventory.size() > 0) {
		inventory[activeSorterIndex].active = true;
		activeSorter = &inventory[activeSorterIndex];
	}
}

void Menu::selectSorter() {
	activeSorter->quantity -= 1;
	world->stairs->activateSorter(activeSorter->sorter);
}

void Menu::showMessage(std::string _message) {
	message = _message;
	clear();
	draw();
}

void Menu::draw() {

	//Draw menu boundaries
	drawBox(start.x, start.y, end.x, end.y);
	drawDivisor(infoSectionStart, start.y, infoSectionStart, end.y);

	//Draw inventory items	
	drawString(start.x + 1, end.y + 1, "Available algorithms");
	drawString(quantitySectionStart + 1, end.y + 1, "Quantity");
	for (int i = 0; i < inventory.size(); i++) {		
		drawString(start.x + 1 + inventory[i].active*2, start.y - 1 - i, inventory[i].name);
		if (inventory[i].active) {
			drawString(start.x + 1, start.y - 1 - i, "\257");
		}

		std::string quantityString;
		for (int j = 1; j <= inventory[i].quantity; j++) {
			quantityString += " \376";
		}
		drawString(quantitySectionStart + 1, start.y - 1 - i, quantityString);
	}

	// Draw message when inventory is empty
	if (inventory.size() <= 0) {
		drawString(start.x + 1, start.y - 1, "Inventory empty...");
	}

	//Draw cofirmation menu
	int xMid = (infoSectionStart + end.x) / 2;;
	int yMid = (start.y + end.y) / 2;
	if (state == ITEM_CONFIRMATION) {
		std::ostringstream stream;
		stream << "Are you sure you want to use " << activeSorter->name << " algorithm?";

		drawCenterString(xMid , yMid , stream.str());
		drawString(xMid - 4, yMid + 2, "Yes");
		drawString(xMid + 2, yMid + 2, "No");
		drawString(xMid - 5 + !confirmation*6, yMid + 2, "\257");
	} else {
		//Draw message		
		drawCenterString(xMid, yMid + 1, message);
	}

	// Draw general info
	std::ostringstream infoStream1;
	std::ostringstream infoStream2;
	infoStream1 << "Sort cycles: " << game->time;
	infoStream2 << "Climbed stairs: " << game->climbedSteps;
	drawString(infoSectionStart + 1, start.y - 1, infoStream1.str() );
	drawString(infoSectionStart + 1, start.y - 2, infoStream2.str() );
}

void Menu::clear() {
	fillSection(start.y + 1, end.y, end.x - start.x, ' ');
}

Algorithm::Algorithm(std::string _name, std::shared_ptr<Sorter> _sorter, int _quantity) {
	name = _name;
	sorter = _sorter;
	quantity = _quantity;
}
