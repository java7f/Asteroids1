#pragma once
#include "Vector2.hpp"
class Entity
{
public:
	Entity();
	~Entity();

	virtual void Update();
	virtual void Render();
	virtual void Warp(int, int);
	virtual void drawEntity();

protected:
	Vector2 position_;
	double mass_;
	int frameHeight_;
	int frameWidth_;
};

