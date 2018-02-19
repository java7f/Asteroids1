#pragma once
#include "Vector2.hpp"
class Entity
{
public:
	//Constructors
	Entity();
	~Entity();

	//Public functions
	virtual void Update();
	virtual void Render();
	virtual void Warp(int, int);
	virtual void DrawEntity();
	virtual void UpdateFrameData(int, int);

protected:
	//Members
	Vector2 position_;
	double mass_;
	int frameHeight_;
	int frameWidth_;
};

