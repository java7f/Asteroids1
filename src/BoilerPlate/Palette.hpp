#pragma once
#include "Color.hpp"

//Class that contains different colors
class Palette
{
public:
	Palette();
	~Palette();
	
	//this functions return a selected color 
	Color getMaroon();
	Color getPurple();
	Color getNavy();
	Color getBlack();
	Color getOrange();

private:
	//Colors that will be available
	Color maroon;
	Color purple;
	Color navy;
	Color black;
	Color orange;
};

