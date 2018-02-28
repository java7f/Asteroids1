#include "Asteroid.hpp"
#include <iostream>
#include "Palette.hpp"
#include <cmath>
#include <time.h>
// OpenGL includes
#include <GL/glew.h>
#include <SDL_opengl.h>

const double IMPULSE_ANGLE = 100;
const int SPAWN_RANGE_LIMIT = 800;

Asteroid::Asteroid(AsteroidSize size)
{
	position_ = Vector2(rand()%SPAWN_RANGE_LIMIT, rand()%SPAWN_RANGE_LIMIT);
	velocity_ = Vector2(0, 0);

	mathTools_ = MathUtilities();
	mass_ = 1.25;
	rotationAngle = 0;
	size_ = size;
	rotationFactor = 120;
	radius_ = 15*size_;

	moveAngle = rand();
	moveValue = 50;
}

Asteroid::Asteroid(AsteroidSize size, Asteroid asteroid)
{
	position_ = Vector2(asteroid.GetPosition().x, asteroid.GetPosition().y);
	velocity_ = Vector2(0, 0);

	mathTools_ = MathUtilities();
	mass_ = 1.25;
	rotationAngle = 0;
	size_ = size;
	rotationFactor = 120;
	radius_ = 15 * size_;

	moveAngle = rand();
	moveValue = 50;
}

Asteroid::~Asteroid()
{
}

//Saves the asteroid data
void Asteroid::PushEntityVertices()
{
	asteroidContainer_.push_back(Vector2(-12.2 * size_, 3.7 * size_));
	asteroidContainer_.push_back(Vector2(-10.6 * size_, 11.6 * size_));
	asteroidContainer_.push_back(Vector2(-2.9 * size_, 10.8 * size_));
	asteroidContainer_.push_back(Vector2(4.9 * size_, 10.9 * size_));
	asteroidContainer_.push_back(Vector2(5 * size_, 5 * size_));
	asteroidContainer_.push_back(Vector2(10.9 * size_, 1.6 * size_));
	asteroidContainer_.push_back(Vector2(12.9 * size_, -7.6 * size_));
	asteroidContainer_.push_back(Vector2(6.1 * size_, -8.4 * size_));
	asteroidContainer_.push_back(Vector2(-2 * size_, -12.3 * size_));
	asteroidContainer_.push_back(Vector2(-5.2 * size_, -6.2 * size_));
	asteroidContainer_.push_back(Vector2(-13.6 * size_, -3.1 * size_));
}

//draws the hit box
void Asteroid::DebuggingHitBox()
{
	int numbersOfLines = 500;
	glColor3d(1.0, 1.0, 1.0);
	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= numbersOfLines; i++) 
	{
		glVertex2d(position_.x + (radius_ * cos(i *  (2 * mathTools_.PI / numbersOfLines))), position_.y + (radius_* sin(i * 2 * mathTools_.PI / numbersOfLines)));
	}
	glEnd();
}

Asteroid::AsteroidSize Asteroid::GetSize()
{
	return size_;
}

void Asteroid::Update(double deltaTime)
{
	//Changes the rotation angle
	rotationAngle += rotationFactor * deltaTime;
	EntityImpulse();
	Entity::Update(deltaTime);
}

void Asteroid::Render()
{
	PushEntityVertices();
	DrawEntity();

	//Decides if the hit box shows or not
	if(isDebugging_)
		DebuggingHitBox();

	//Cleaning up asteroid vector
	asteroidContainer_.clear();
}

//draws the asteroid
void Asteroid::DrawEntity()
{
	glLoadIdentity();
	glColor3d(1.0, 1.0, 1.0);
	glTranslated(position_.x, position_.y, 0.0);
	glRotated(rotationAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i=0; i< asteroidContainer_.size(); i++)
	{
		glVertex2d(asteroidContainer_[i].x, asteroidContainer_[i].y);
	}
	glEnd();
}

//Increments the velocity
void Asteroid::EntityImpulse()
{
	if (mass_ > 0)
	{
		velocity_.x = (moveValue/mass_)* sin(mathTools_.ToRadians(moveAngle));
		velocity_.y = (moveValue/mass_)* cos(mathTools_.ToRadians(moveAngle));
	}
}
