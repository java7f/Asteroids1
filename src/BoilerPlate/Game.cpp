#include "Game.hpp"


Game::Game()
{
	player = Player();
	PushAsteroids();
}


Game::~Game()
{
}

void Game::RenderGame()
{
	player.Render();
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].Render();
	}
	DebuggingLine();
}

void Game::UpdateGame(double DESIRED_FRAME_TIME, double m_height, double m_width)
{
	player.UpdateFrameData(m_height, m_width);
	// Update code goes here
	player.Update(DESIRED_FRAME_TIME);
	for (int i = 0; i < asteroids.size(); i++)
	{
		asteroids[i].UpdateFrameData(m_height, m_width);
		asteroids[i].Update(DESIRED_FRAME_TIME);
	}
}

void Game::DebuggingLine()
{
	glLoadIdentity();

	double radius = 5 * player.getRadius();
	double distanceToAsteroid, shipX, shipY, asteroidX, asteroidY;

	if (player.getDebuggingStatus())
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < asteroids.size(); i++)
		{
			shipX = player.getPosition().x + radius;
			shipY = player.getPosition().y + radius;

			asteroidX = asteroids[i].getPosition().x + asteroids[i].getRadius();
			asteroidY = asteroids[i].getPosition().y + asteroids[i].getRadius();

			distanceToAsteroid = sqrt(pow(shipX - asteroidX, 2) + pow(shipY - asteroidY, 2));

			if (distanceToAsteroid <= radius)
			{
				glVertex2d(player.getPosition().x, player.getPosition().y);
				glVertex2d(asteroids[i].getPosition().x, asteroids[i].getPosition().y);
			}
		}
		glEnd();
	}
	
}

void Game::PushAsteroids()
{
	for (int i = 0; i < 10; i++)
	{
		asteroids.push_back(Asteroid(Asteroid::BIG));
	}
}