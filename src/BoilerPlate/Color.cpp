#include "Color.hpp"


Color::Color()
{
	redlvl = 0.0;
	greenlvl = 0.0;
	bluelvl = 0.0;
	opacitylvl = 0.0;
}

Color::Color(float redValue, float greenValue, float blueValue, float opacityValue)
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

float Color::getRedValue()
{
	return redlvl;
}

float Color::getGreenValue()
{
	return greenlvl;
}

float Color::getBlueValue()
{
	return bluelvl;
}

float Color::getOpacityValue()
{
	return opacitylvl;
}
