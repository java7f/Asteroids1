#pragma once
#include "Vector2.hpp"
class Player
{
public:
	Player();
	~Player();
	void Update();
	void Render();
	void Move(Vector2&);

	bool isWPressed;

private:
	Vector2 position;
};

