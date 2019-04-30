//Author: Ondrej Slama
//Date of last change: 07.01.2019
//Developed in Visual Studio 
//Created as a school project in Brno University of technology
//All the code which isn't marked with "confesion" comment is authentic and only those marked function are copied from the internet
//Game automatically starts in fullscreen. To prevent that, just comment the fullScreenConsole() line.

#include "Base.h"
#include "World.h"
#include "Game.h"
#include <io.h>
#include <fcntl.h>

int columns, rows;

int main(){	
	fullScreenConsole(); // Set the console to fullscreen (from ConsoleDraw.h)
	getColumnsAndRows(&columns, &rows); // Get current number of columns and rows

	std::shared_ptr<Game> g = std::make_shared<Game>(rows, columns); // where all the magic happens

	while (!g->gameFinished){
		Sleep(30);
		g->update(); // update the game
		g->draw(); // draw the game
	}
	return 0;
}

