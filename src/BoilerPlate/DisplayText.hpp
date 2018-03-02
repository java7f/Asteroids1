#pragma once
#include <iostream>
#include <SDL_opengl.h>
#include <SDL.h>
#include <SDL_ttf.h>
class DisplayText
{
public:
	DisplayText(double, double, int);
	~DisplayText();
	bool InitializeFont();
	void CleanUp();
	void FontRender(std::string, SDL_Color, float, float, int);
	unsigned int PowerOfTwo(unsigned int);

private:
	TTF_Font *gameFont_;
	double frameHeight_;
	double frameWidht_;
};

