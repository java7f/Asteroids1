#pragma once
#include "Vector2.hpp"
#include "MathUtilities.hpp"
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

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
	virtual void setDebuggingState(bool);
	virtual Vector2 getPosition();
	virtual bool getDebuggingStatus();
	virtual double getRadius();

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
	bool isDebugging;
};

