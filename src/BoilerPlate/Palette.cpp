#include "Palette.hpp"


Palette::Palette()
{
	//initialization of the colors using the respective values 
	maroon = Color(0.502f, 0.000f, 0.000f, 1.0f);
	purple = Color(0.502f, 0.000f, 0.502f, 1.0f);
	navy = Color(0.000f, 0.000f, 0.502f, 1.0f);
	gray = Color(0.439f, 0.502f, 0.565f, 1.0f);
	orange = Color(1.000f, 0.647f, 0.000f, 1.0f);
}


Palette::~Palette()
{
}

Color Palette::getMaroon()
{
	return maroon;
}

Color Palette::getPurple()
{
	return purple;
}

Color Palette::getNavy()
{
	return navy;
}

Color Palette::getGray()
{
	return gray;
}

Color Palette::getOrange()
{
	return orange;
}
