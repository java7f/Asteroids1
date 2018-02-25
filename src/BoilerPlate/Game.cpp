#include "Game.hpp"

//Global variables
double radiusForMeasurement;
double distanceToAsteroid;
double shipX, shipY;
double asteroidX, asteroidY;

Game::Game()
{
	player_ = Player();
	PushAsteroids();
	mathTools_ = MathUtilities();
}


Game::~Game()
{
}

void Game::RenderGame()
{
	//Rendering the entities of the game
	player_.Render();
	for (int i = 0; i < asteroids_.size(); i++)
	{
		asteroids_.at(i).Render();
	}
	DebuggingLine();
}

void Game::UpdateGame(double DESIRED_FRAME_TIME, double m_height, double m_width)
{
	player_.UpdateFrameData(m_height, m_width);
	player_.Update(DESIRED_FRAME_TIME);
	for (int i = 0; i < asteroids_.size(); i++)
	{
		asteroids_[i].UpdateFrameData(m_height, m_width);
		asteroids_[i].Update(DESIRED_FRAME_TIME);
	}
}

//Draws a line between the player and the asteroids close to it
void Game::DebuggingLine()
{
	glLoadIdentity();

	radiusForMeasurement = 2 * player_.GetRadius();

	if (player_.GetDebuggingStatus())
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < asteroids_.size(); i++)
		{
			shipX = player_.GetPosition().x;
			shipY = player_.GetPosition().y;

			asteroidX = asteroids_[i].GetPosition().x;
			asteroidY = asteroids_[i].GetPosition().y;

			distanceToAsteroid = mathTools_.DistanceBetweenTwoPoints(shipX, shipY, asteroidX, asteroidY);

			if (distanceToAsteroid <= radiusForMeasurement + asteroids_[i].GetRadius())
			{
				glVertex2d(player_.GetPosition().x, player_.GetPosition().y);
				glVertex2d(asteroids_[i].GetPosition().x, asteroids_[i].GetPosition().y);
			}
		}
		glEnd();
	}
	
}

void Game::PushAsteroids()
{
	for (int i = 0; i < 10; i++)
	{
		asteroids_.push_back(Asteroid(Asteroid::SMALL));

	}
}