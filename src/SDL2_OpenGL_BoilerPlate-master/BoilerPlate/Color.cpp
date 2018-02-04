#include "Color.h"


Color::Color()
{
	redlvl = 0.0;
	greenlvl = 0.0;
	bluelvl = 0.0;
	opacitylvl = 0.0;
}

Color::Color(double redValue, double greenValue, double blueValue, double opacityValue)
{
	redlvl = redValue;
	greenlvl = greenValue;
	bluelvl = blueValue;
	opacitylvl = opacityValue;
}


Color::~Color()
{
	redlvl = NULL;
	greenlvl = NULL;
	bluelvl = NULL;
	opacitylvl = NULL;
}

double Color::getRedValue()
{
	return redlvl;
}

double Color::getGreenValue()
{
	return greenlvl;
}

double Color::getBlueValue()
{
	return bluelvl;
}

double Color::getOpacityValue()
{
	return opacitylvl;
}

void Color::setRed(double redValue)
{
	redlvl = redValue;
}

void Color::setGreen(double greenValue)
{
	greenlvl = greenValue;
}

void Color::setBlue(double blueValue)
{
	bluelvl = blueValue;
}

void Color::setOpacity(double opacityValue)
{
	opacitylvl = opacityValue;
}
