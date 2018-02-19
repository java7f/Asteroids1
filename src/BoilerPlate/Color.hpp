#pragma once
#include <stdlib.h>

//Class that will contain the values of the color wanted
class Color
{
public:
	Color();
	Color(double redValue, double greenValue, double blueValue, double opacityValue); //parameterized constructor
	~Color();

	//this functions return the values of the fields used in the RGBA system
	double getRedValue();
	double getGreenValue();
	double getBlueValue();
	double getOpacityValue();

	//this functions set the values of the fields used in the RGBA system
	void setRed(double redValue);
	void setGreen(double greenValue);
	void setBlue(double blueValue);
	void setOpacity(double opacityValue);

private:
	double redlvl;
	double greenlvl;
	double bluelvl;
	double opacitylvl;
};

