#pragma once
#include "Vector2.hpp"
#include "MathUtilities.hpp"
#include "OpenGL_Includes.hpp"

class Entity
{
public:
	//Constructors
	Entity();
	~Entity();

	//Public functions
	virtual void Update(double);
	virtual void Render();
	virtual void Warp(double, double);
	virtual void DrawEntity();
	virtual void UpdateFrameData(double, double);
	virtual void EntityImpulse();
	virtual void PushEntityVertices();
	virtual void DebuggingHitBox();
	virtual void ChangeDebuggingState();
	virtual Vector2 GetPosition();
	virtual bool GetDebuggingStatus();
	virtual double GetRadius();
	virtual void SetAliveState(bool);
	double GetRotationAngle();
	virtual bool GetAliveStatus();

	//Global variables
	double rotationAngle;
	double moveValue;
	bool isAlive;

protected:
	//Members
	Vector2 position_;
	Vector2 velocity_;
	MathUtilities mathTools_;
	double mass_;
	double frameHeight_;
	double frameWidth_;
	double radius_;
	bool isDebugging_;
};

