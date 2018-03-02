#pragma once
#include <stdlib.h>

//Class that will contain the values of the color wanted
class Color
{
public:
	Color();
	Color(float redValue, float greenValue, float blueValue, float opacityValue); //parameterized constructor
	~Color();

	//this functions return the values of the fields used in the RGBA system
	float getRedValue();
	float getGreenValue();
	float getBlueValue();
	float getOpacityValue();

private:
	float redlvl;
	float greenlvl;
	float bluelvl;
	float opacitylvl;
};

