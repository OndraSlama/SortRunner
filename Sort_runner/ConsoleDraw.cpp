#include "Base.h"

//Small library for needs of drawing specific object to console
//There are some unused function which become obsolete during development

void fullScreenConsole() {		//(confesion: found on stack overflow)
	// Fullscreen console
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
}

//Get the number of columns and rows
void getColumnsAndRows(int* columns, int* rows) { //(confesion: found on stack overflow)
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	*columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	*rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

void gotoxy(int x, int y) { // bread and butter of this library (confesion: found on stack overflow)
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}

void clearScreen(char fill) {  //	(confesion: found on stack overflow) - unused
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void fillSection(int yStart, int yEnd, int columns, char fill) { //newer and better than clearScreen
	gotoxy(0, yEnd);
	std::string lineToFill = "";
	for (int j = 0; j < abs(yStart - yEnd); j++) {
		for (int i = 0; i < columns; i++) {
			lineToFill += fill;
		}
		if(j != abs(yStart - yEnd) - 1)	lineToFill += "\n";
	}
	std::cout << lineToFill;
}

void line(int x, int y, int endx, int endy){ // Recursive function for drawing line from any 2 points (unnecessary)
	
	if (y == endy) {
		gotoxy(min(x, endx), y);
		std::string lineToFill = "";
		for (int i = 0; i < abs(endx - x); i++){
			lineToFill += "_";
		}
		std::cout << lineToFill;
	}
	else {
		if (x == endx && y == endy)
			return;

		int xDist = endx - x;
		int yDist = endy - y;
		int xLines = sgn(xDist);
		int yLines = sgn(yDist);
		if (xDist != 0 && yDist != 0) {

			float slope = abs((float)yDist / (float)xDist);
			if (abs(slope) >= 1) {
				yLines = round(yLines * slope);
			}
			else {
				xLines = round((float)xLines * 1 / slope);
			}
		}

		for (int i = 0; i < abs(xLines); i++) {
			gotoxy(x, y);
			std::cout << '_';
			x += sgn(xLines);
		}

		for (int i = 0; i < abs(yLines); i++) {
			if (sgn(yLines) > 0) {
				y += sgn(yLines);
			}

			gotoxy(x, y);
			std::cout << '|';

			if (sgn(yLines) < 0) {
				y += sgn(yLines);
			}

			if (i == abs(yLines) - 1)
				x += abs(xLines);
		}

		line(x, y, endx, endy);
	}
}

void clearLine(int x, int y, int endx, int endy){
	gotoxy(x, y);
	std::string lineToFill = "";
	for (int i = 0; i < abs(endx-x); i++)	{
		lineToFill += " "; 		
	}
	std::cout << lineToFill;
}


void step(int x, int y, int height){ // function for drawing one step
	int startY = y;
	while ((startY - y) < height){
		gotoxy(x - 1, y);
		std::cout << '|';
		gotoxy(x + 1, y);
		std::cout << '|';
		y--;
	}
	gotoxy(x, y);
	std::cout << '_';
}

void clearStep(int x, int y, int height) { // function for clearing one step
	int startY = y;
	while ((startY - y) < height) {
		gotoxy(x - 1, y);
		std::cout << " ";
		gotoxy(x + 1, y);
		std::cout << " ";
		y--;
	}
	gotoxy(x, y);
	std::cout << " ";
}

void drawSteps(int x, int y, int endx, int endy, std::vector<int> steps){ // better and optimized way of drawing the stairs (used to draw one step by step)
	int length = abs(endx - x);
	int height = abs(y - endy);
	std::string lineToFill = ""; // buffering lines results to much faster rendering than outputing character per time
	std::string character = "";
	int stepIndex = 0;
	if (steps.size() == 0) return;

	for (int i = 0; i <= height; i++){
		lineToFill = "";
		for (int j = 0; j <= length; j++)	{
			
			stepIndex = floor(j / 2);

			character = " ";
			// even number -> vertical lines
			if (j % 2 == 0) { 
				if (steps[min(stepIndex, steps.size()-1)] > i || steps[max(stepIndex - 1, 0)] > i) {
					character = "|";
				}
			}
			// odd number -> horizontal line
			else {
				if (steps[stepIndex] == i) {
					character = "_";
				}
			}
			lineToFill += character;			
		}

		gotoxy(x, y - i);
		std::cout << lineToFill;
	}
}

void clearBlock(int x, int y, int endx, int endy) { // clear block of characters
	gotoxy(x, endy);
	std::string lineToFill = "";
	for (int i = 0; i <= abs(endx-x); i++)	{
		lineToFill += " ";
	}
	for (int i = endy; i <= y; i++) {
		gotoxy(x, i);
		std::cout << lineToFill;
	}
}

void drawString(int x, int y, std::string string){// Draw string to x, y position
	gotoxy(x, y);
	std::cout << string;
}

void drawCenterString(int x, int y, std::string string) { // Draw centered string to x, y position
	gotoxy(x - string.length()/2, y);
	std::cout << string;
}

void drawStickman(int x, int y){
	gotoxy(x + 1, y);
	std::cout << (char)186;
	gotoxy(x, y - 1);
	std::cout << "/" << (char)219 << "\\";
	gotoxy(x + 1, y - 2);
	std::cout << "o";
}

void drawHappyStickman(int x, int y) {
	gotoxy(x, y - 2);
	std::cout << "\\o/";
	gotoxy(x + 1, y - 1);
	std::cout << (char)219;
	gotoxy(x + 1, y);
	std::cout << (char)186;
}

void drawHeaven(int x, int y) { // draw heaven gate
	gotoxy(x, y - 4);
	std::cout << "HEAVEN";
	gotoxy(x, y - 3);
	std::cout << " ____ ";
	gotoxy(x, y - 2);
	std::cout << "|    |";
	gotoxy(x, y-1);
	std::cout << "|    |";
	gotoxy(x, y);
	std::cout << "|";
	gotoxy(x+5, y);
	std::cout << "|";
}

void drawBox(int x, int y, int endX, int endY) {	// draw outer boundaries of a box (for menu)
	for (int i = 0; i <= y - endY; i++) {
		std::ostringstream stream;
		if (i == 0) {
			stream << "\300";
			for (int j = 1; j < endX - x; j++) {
				stream << "\304";
			}
			stream << "\331";
		} else if (i == y - endY) {
			stream << "\332";
			for (int j = 1; j < endX - x; j++) {
				stream << "\304";
			}
			stream << "\277";
		} else {
			stream << "\263";
			for (int j = 1; j < endX - x; j++) {
				stream << " ";
			}
			stream << "\263";
		}
		gotoxy(x, y - i);
		std::cout << stream.str();
	}
}

void drawDivisor(int x, int y, int endX, int endY) {
	gotoxy(x, y);
	std::cout << "\301";
	for (int i = 1; i < y-endY; i++) {
		gotoxy(x, y - i);
		std::cout << "\263";
	}
	gotoxy(x, endY);
	std::cout << "\302";
}


