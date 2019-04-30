#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <string>

void fullScreenConsole();
void getColumnsAndRows(int* columns, int* rows);
void gotoxy(int x, int y);
void clearScreen(char fill = ' ');
void fillSection(int yStart, int yEnd, int columns, char fill);
void line(int x, int y, int endx, int endy);
void clearLine(int x, int y, int endx, int endy);
void step(int x, int y, int height);
void clearStep(int x, int y, int height);
void drawSteps(int x, int y,int endx,int endy, std::vector<int> steps);
void clearBlock(int x, int y, int endx, int endy);
void drawString(int x, int y, std::string string);
void drawCenterString(int x, int y, std::string string);
void drawStickman(int x, int y);
void drawHappyStickman(int x, int y);
void drawHeaven(int x, int y);
void drawBox(int x, int y,int endX,int endY);
void drawDivisor(int x, int y, int endX, int endY);