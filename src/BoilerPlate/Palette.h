#pragma once
#include "Color.h"

class Palette
{
public:
	Palette();
	~Palette();
	Color getYellow();
	Color getPurple();
	Color getNavy();
	Color getGray();
	Color getOrange();

private:
	Color yellow;
	Color purple;
	Color navy;
	Color gray;
	Color orange;
};

