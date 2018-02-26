#include "Game.hpp"

//Global variables
double radiusForMeasurement;
double distanceToAsteroid;
double shipX, shipY;
double asteroidX, asteroidY;
double bulletX, bulletY;

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

	for (int i = 0; i < playerBullets_.size(); i++)
	{
		playerBullets_.at(i).Render();
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

	for (int i = 0; i < playerBullets_.size(); i++)
	{
		playerBullets_[i].UpdateFrameData(m_height, m_width);
		playerBullets_[i].Update(player_, DESIRED_FRAME_TIME);
		if (!playerBullets_[i].GetAliveStatus())
			playerBullets_.erase(playerBullets_.begin() + i);
	}

	PlayerCollision();
	BulletCollision();
}

//Draws a line between the player and the asteroids close to it
void Game::DebuggingLine()
{
	glLoadIdentity();

	radiusForMeasurement = 2 * player_.GetRadius();

	if (player_.GetDebuggingStatus())
	{
		shipX = player_.GetPosition().x;
		shipY = player_.GetPosition().y;

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < asteroids_.size(); i++)
		{
			asteroidX = asteroids_[i].GetPosition().x;
			asteroidY = asteroids_[i].GetPosition().y;

			distanceToAsteroid = mathTools_.DistanceBetweenTwoPoints(shipX, shipY, asteroidX, asteroidY);

			if (distanceToAsteroid <= radiusForMeasurement + asteroids_[i].GetRadius())
			{
				glVertex2d(shipX, shipY);
				glVertex2d(asteroidX, asteroidY);
			}
		}
		glEnd();
	}
	
}

void Game::PushAsteroids()
{
	for (int i = 0; i < 10; i++)
	{
		asteroids_.push_back(Asteroid(Asteroid::BIG));

	}
}

void Game::ShootBullets()
{
	if (player_.GetAliveStatus() && playerBullets_.size() < 5)
	{
		Ammo newBullet = Ammo(player_);
		if (player_.GetDebuggingStatus())
			newBullet.ChangeDebuggingState();
		playerBullets_.push_back(newBullet);
	}
}

void Game::PlayerCollision()
{
	for (int i = 0; i < asteroids_.size(); i++)
	{
		if (CollidingDetection(player_, asteroids_[i]) && !player_.GetDebuggingStatus())
		{
			player_.SetAliveState(false);
		}
	}
}

void Game::BulletCollision()
{
	bool ifCollision = false;

	for (int i = 0; i < asteroids_.size(); i++)
	{
		for (int j = 0; j < playerBullets_.size(); j++)
		{
			if (CollidingDetection(asteroids_[i], playerBullets_[j]))
			{
				if (asteroids_[i].GetSize() == Asteroid::BIG)
				{
					asteroids_.push_back(Asteroid(Asteroid::MEDIUM, asteroids_[i]));
					asteroids_.push_back(Asteroid(Asteroid::MEDIUM, asteroids_[i]));
					asteroids_.erase(asteroids_.begin() + i);
					playerBullets_.erase(playerBullets_.begin() + j);
					ifCollision = true;
				}
				else if (asteroids_[i].GetSize() == Asteroid::MEDIUM)
				{
					asteroids_.push_back(Asteroid(Asteroid::SMALL, asteroids_[i]));
					asteroids_.push_back(Asteroid(Asteroid::SMALL, asteroids_[i]));
					asteroids_.erase(asteroids_.begin() + i);
					playerBullets_.erase(playerBullets_.begin() + j);
					ifCollision = true;
				}
				else
				{
					asteroids_.erase(asteroids_.begin() + i);
					playerBullets_.erase(playerBullets_.begin() + j);
					ifCollision = true;
				}
			}
			break;
		}
		if (ifCollision) 
			break;
	}
}

void Game::AddAsteroids()
{
	if (player_.GetDebuggingStatus())
	{
		Asteroid newAsteroid = Asteroid(newAsteroid.SMALL);
		newAsteroid.ChangeDebuggingState();
		asteroids_.push_back(newAsteroid);
	}
	
}

void Game::DeleteAsteroids()
{
	if (asteroids_.size()>0)
		asteroids_.pop_back();
}

void Game::DebuggingModeToggle()
{
	if(!player_.GetAliveStatus())
		player_.PlayerRespawn();
	player_.ChangeDebuggingState();	
	player_.SetAliveState(true);
	for (int i = 0; i < asteroids_.size(); i++)
	{
		asteroids_[i].ChangeDebuggingState();
	}
	for (int i = 0; i < playerBullets_.size(); i++)
	{
		playerBullets_[i].ChangeDebuggingState();
	}
}

bool Game::CollidingDetection(Entity firstEntity, Entity secondEntity)
{
	Vector2 first = firstEntity.GetPosition();
	Vector2 second = secondEntity.GetPosition();

	distanceToAsteroid = mathTools_.DistanceBetweenTwoPoints(first.x, first.y, second.x, second.y);

	if (distanceToAsteroid <= (firstEntity.GetRadius() + secondEntity.GetRadius()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Game::InputManager()
{

}
