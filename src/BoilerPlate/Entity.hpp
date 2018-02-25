#pragma once
#include "Vector2.hpp"
#include "MathUtilities.hpp"
class Entity
{
public:
	//Constructors
	Entity();
	~Entity();

	//Public functions
	virtual void Update(double);
	virtual void Render();
	virtual void Warp(int, int);
	virtual void DrawEntity();
	virtual void UpdateFrameData(int, int);
	virtual void EntityImpulse();
	virtual void PushEntityVertices();

protected:
	//Members
	Vector2 position_;
	Vector2 velocity_;
	MathUtilities mathTools_;
	double mass_;
	int frameHeight_;
	int frameWidth_;
	double radius_;
	double rotationAngle;
};

