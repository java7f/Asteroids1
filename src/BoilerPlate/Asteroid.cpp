#include "Asteroid.hpp"
#include <iostream>
#include "Palette.hpp"
#include <cmath>
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

const double IMPULSE_ANGLE = 100;

Asteroid::Asteroid(AsteroidSize size)
{
	position_ = Vector2(rand()%800, rand()%800);
	velocity_ = Vector2(0, 0);
	mathTools_ = MathUtilities();
	mass_ = 0.87;
	rotationAngle = 0;
	size_ = size;
	rotationFactor = 120;
}

Asteroid::~Asteroid()
{
}

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

void Asteroid::Update(double deltaTime)
{
	rotationAngle += rotationFactor * deltaTime;
	EntityImpulse();
	Entity::Update(deltaTime);
}

void Asteroid::Render()
{
	glLoadIdentity();
	glTranslated(position_.x, position_.y, 0.0);
	glRotated(rotationAngle, 0.0, 0.0, 1.0);
	PushEntityVertices();
	DrawEntity();
	asteroidContainer_.clear();
}

void Asteroid::DrawEntity()
{
	glBegin(GL_LINE_LOOP);
	for (int i=0; i< asteroidContainer_.size(); i++)
	{
		glVertex2d(asteroidContainer_[i].x, asteroidContainer_[i].y);
	}
	glEnd();
}

void Asteroid::EntityImpulse()
{
	double moveValue = 50;
	velocity_.x = (moveValue)* sin(mathTools_.ToRadians(500));
	velocity_.y = (moveValue)* cos(mathTools_.ToRadians(500));
}
