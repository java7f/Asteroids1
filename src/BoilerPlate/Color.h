#pragma once
#include <stdlib.h>
class Color
{
public:
	Color();
	Color(double redValue, double greenValue, double blueValue, double opacityValue);
	~Color();

	double getRedValue();
	double getGreenValue();
	double getBlueValue();
	double getOpacityValue();

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

