#include "MathUtilities.h"



MathUtilities::MathUtilities()
{
}


MathUtilities::~MathUtilities()
{
}

const double MathUtilities::PI = 3.14159265;

int MathUtilities::floatToInt(float number)
{
	return number+0.5;
}

int MathUtilities::floatToEvenInt(float number)
{
	int returningInt = number + 0.5;
	if (returningInt % 2 == 0)
	{
		return returningInt;
	}
	else
	{
		return returningInt + 1;
	}
}

double MathUtilities::toRadians(double angle)
{
	return ((angle*3.14)/180);
}

double MathUtilities::toDegrees(double angle)
{
	return ((angle*180)/3.14);
}

bool MathUtilities::isPowerTwo(int number)
{
	double value = log2(number);
	if (fmod(value, 1) == 0.0) //function that checks if the number is an integer
	{
		return true;
	}
	else
		return false;
}

double MathUtilities::angularDistanceR(double angle1, double angle2)
{
	double result = angle1 - angle2;
	if (result < 0)
		result += (2*3.14);
	return result;
}

double MathUtilities::angularDistanceD(double angle1, double angle2)
{
	double result = angle1 - angle2;
	if (result < 0)
		result += 360;
	return result;
}
