#pragma once
#include <vector>
#include <memory>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm> 
#include "ConsoleDraw.h"

class Vector2D
{
public:
	int x, y;
	Vector2D();
	void set(int _x, int _y);
	~Vector2D();
};
