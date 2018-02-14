#pragma once
#include "Vector2.hpp"
#include "MathUtilities.h"
class Player
{
public:

	//Constructors
	Player();
	~Player();

	//Public functions
	void Update();
	void Render();
	void drawShip();
	void Move(Vector2&);
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void Warp(int, int);
	void setMovingForwardState(bool);
	void updateFrameData(int, int);

private:
	//Attributes
	Vector2 position;
	bool isMovingForward;
	double rotationAngle;
	double shipMass;
	int frameHeight;
	int frameWidth;
	MathUtilities mathToools;
};

