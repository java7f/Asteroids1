#pragma once
#include "Vector2.hpp"
#include "MathUtilities.hpp"
// OpenGL includes
#include <GL/glew.h>
#include <SDL_opengl.h>

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
	virtual void DebuggingHitBox();
	virtual void ChangeDebuggingState();
	virtual Vector2 GetPosition();
	virtual bool GetDebuggingStatus();
	virtual double GetRadius();
	virtual void SetAliveState(bool);
	double GetRotationAngle();
	virtual bool GetAliveStatus();

protected:
	//Members
	Vector2 position_;
	Vector2 velocity_;
	MathUtilities mathTools_;
	double mass_;
	int frameHeight_;
	int frameWidth_;
	double radius_;
	bool isDebugging_;

	double rotationAngle;
	double moveValue;
	bool isAlive;
};

