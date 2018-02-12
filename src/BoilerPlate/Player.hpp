#pragma once
#include "Vector2.hpp"
class Player
{
public:

	//Constructors
	Player();
	~Player();

	//Public functions
	void Update();
	void Render();
	void Move(Vector2&);
	void Warp(int, int);
	void setMovingForwardState(bool);
	void updateFrameData(int, int);

private:
	//Attributes
	Vector2 position;
	bool isMovingForward;
	int frameHeight;
	int frameWidth;
};

