#pragma once
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

//Class that contains different math functions
class MathUtilities
{
public:
	MathUtilities();
	~MathUtilities();
	int floatToInt(float number); //rounds to the nearest integer
	int floatToEvenInt(float number); //rounds to the nearest even number
	double toRadians(double angle); //converts from degrees to radians	
	double toDegrees(double angle); //converts fron radians to degrees
	bool isPowerTwo(int number); //checks if a number is a power of two


	//clamps a number to the range specified
	template <typename type>
	type clamp(type number, type minimum, type maximum)
	{
		if (number < minimum)
			number= minimum;
		else if(number > maximum)
			number= maximum;

		return number;
	}

	//returns maximum number of two given
	template <typename type> 
	type getMaxNumber(type number1, type number2)
	{
		if (number1 > number2)
			return number1;
		else
			return number2;
	}

	//returns maximum number of three given
	template <typename type>
	type getMaxNumber(type number1, type number2, type number3)
	{
		type values[] = { number1, number2, number3 };
		sort(values, values+3);
		
		return values[2];
	}

	//returns maximum number of four given
	template <typename type>
	type getMaxNumber(type number1, type number2, type number3, type number4)
	{
		type values[] = { number1, number2, number3, number4 };
		sort(values, values + 4);
		return values[3];
	}

	//returns minimum number of two given
	template <typename type>
	type getMinNumber(type number1, type number2)
	{
		if (number1 < number2)
			return number1;
		else
			return number2;
	}

	//returns minimum number of three given
	template <typename type>
	type getMinNumber(type number1, type number2, type number3)
	{
		type values[] = { number1, number2, number3 };
		sort(values, values + 3);

		return values[0];
	}

	//returns minimum number of four given
	template <typename type>
	type getMinNumber(type number1, type number2, type number3, type number4)
	{
		type values[] = { number1, number2, number3, number4 };
		sort(values, values + 4);
		return values[0];
	}
};

