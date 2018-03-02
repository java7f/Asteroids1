#pragma once
#include <iostream>
#include "OpenGL_Includes.hpp"
class DisplayText
{
public:
	//Constructors
	DisplayText(double, double, int);
	~DisplayText();

	//Functions
	bool InitializeFont();
	void CleanUp();
	void FontRender(std::string, SDL_Color, float, float, int);
	unsigned int PowerOfTwo(unsigned int);

private:
	//Members
	TTF_Font *gameFont_;
	double frameHeight_;
	double frameWidht_;
};

