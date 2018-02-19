#include "Asteroid.hpp"
#include "Palette.h"
#include <cmath>
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>



Asteroid::Asteroid(AsteroidSize size)
{
	Entity();
	size_ = size;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update()
{
}

void Asteroid::Render()
{
	drawEntity();
}

void Asteroid::drawEntity()
{
	asteroidContainer_.push_back(Vector2(0*size_, 40*size_));
	asteroidContainer_.push_back(Vector2(14 * size_, 34 * size_));
	asteroidContainer_.push_back(Vector2(12 * size_, 20 * size_));
	asteroidContainer_.push_back(Vector2(6 * size_, 6 * size_));
	asteroidContainer_.push_back(Vector2(-10 * size_, 10 * size_));
	asteroidContainer_.push_back(Vector2(-10 * size_, 20 * size_));
	asteroidContainer_.push_back(Vector2(-20 * size_, 30 * size_));
	asteroidContainer_.push_back(Vector2(-6 * size_, 34 * size_));

	glLoadIdentity();
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < asteroidContainer_.size(); i++)
	{
		glVertex2f((asteroidContainer_.at(i).x), (asteroidContainer_.at(i).y));
	}
	glEnd();
}
