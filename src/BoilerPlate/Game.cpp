#include "Game.hpp"

Game::Game()
{
	player_ = Player();
	PushAsteroidsPerRound();
	mathTools_ = MathUtilities();
	graphColor = Palette();
	orange = graphColor.getOrange();
	deltaTimeContainer_ = std::vector<Vector2>(MAXIMUM_FRAME_CAPACITY);
	PushDeltaTimeValues();
	playerLives_ = 3; 
	roundCounter = 0;
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

	RenderFramePlot();
	DebuggingLine();
}

void Game::UpdateGame(double deltaTime, double m_height, double m_width)
{
	player_.UpdateFrameData(m_height, m_width);
	player_.Update(deltaTime);
	for (int i = 0; i < asteroids_.size(); i++)
	{
		asteroids_[i].UpdateFrameData(m_height, m_width);
		asteroids_[i].Update(deltaTime);
	}

	for (int i = 0; i < playerBullets_.size(); i++)
	{
		playerBullets_[i].UpdateFrameData(m_height, m_width);
		playerBullets_[i].Update(player_, deltaTime);
		if (!playerBullets_[i].GetAliveStatus())
			playerBullets_.erase(playerBullets_.begin() + i);
	}

	if (GetAsteroidsNumber() == 0)
	{
		std::cout << "hola";
		roundCounter++;
		PushAsteroidsPerRound();
	}

	//Checking collisions
	PlayerCollision();
	BulletCollision();

	//Manages input
	GameInputManager();
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
		glColor3d(1.0, 1.0, 1.0);

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

		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < asteroids_.size(); i++)
		{
			asteroidX = asteroids_[i].GetPosition().x;
			asteroidY = asteroids_[i].GetPosition().y;
			for (int j = 0; j < playerBullets_.size(); j++)
			{
				bulletX = playerBullets_[j].GetPosition().x;
				bulletY = playerBullets_[j].GetPosition().y;
				radiusForMeasurement = 2 * playerBullets_[j].GetRadius();
				distanceToAsteroid = mathTools_.DistanceBetweenTwoPoints(bulletX, bulletY, asteroidX, asteroidY);
				if (distanceToAsteroid <= radiusForMeasurement + asteroids_[i].GetRadius())
				{
					glVertex2d(bulletX, bulletY);
					glVertex2d(asteroidX, asteroidY);
				}
			}
		}
		glEnd();
	}
}

//Creates initial asteroids
void Game::PushAsteroidsPerRound()
{
	for (int i = 0; i < (INITIAL_ASTEROIDS + roundCounter); i++)
	{
		asteroids_.push_back(Asteroid(Asteroid::BIG));
	}
}

//Shooting the bullets
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

//Controls the collision between the ship and asteroids
void Game::PlayerCollision()
{
	for (int i = 0; i < asteroids_.size(); i++)
	{
		if (CollidingDetection(player_, asteroids_[i]) && !player_.GetDebuggingStatus())
		{
			player_.SetAliveState(false);
			playerLives_--;
		}
	}
}

//Controls the collision between the bullet and asteroids
void Game::BulletCollision()
{
	if (!player_.GetDebuggingStatus()) {
		bool ifCollision = false;

		for (int i = 0; i < asteroids_.size(); i++)
		{
			for (int j = 0; j < playerBullets_.size(); j++)
			{
				if (CollidingDetection(asteroids_[i], playerBullets_[j]))
				{
					//Checking the size of the asteroid and splitting them
					if (asteroids_[i].GetSize() == Asteroid::BIG)
					{
						asteroids_.push_back(Asteroid(Asteroid::MEDIUM, asteroids_[i]));
						asteroids_.push_back(Asteroid(Asteroid::MEDIUM, asteroids_[i]));
						if (player_.GetDebuggingStatus())
						{
							asteroids_.at(asteroids_.size() - 1).ChangeDebuggingState();
							asteroids_.at(asteroids_.size() - 2).ChangeDebuggingState();
						}
						asteroids_.erase(asteroids_.begin() + i);
						playerBullets_.erase(playerBullets_.begin() + j);
						ifCollision = true;
					}
					else if (asteroids_[i].GetSize() == Asteroid::MEDIUM)
					{
						asteroids_.push_back(Asteroid(Asteroid::SMALL, asteroids_[i]));
						asteroids_.push_back(Asteroid(Asteroid::SMALL, asteroids_[i]));
						if (player_.GetDebuggingStatus())
						{
							asteroids_.at(asteroids_.size() - 1).ChangeDebuggingState();
							asteroids_.at(asteroids_.size() - 2).ChangeDebuggingState();
						}
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
					break;
				}
			}
			if (ifCollision)
				break;
		}
	}
}

//Creates asteroids in debugging mode
void Game::AddAsteroidsInDebugging()
{
	if (player_.GetDebuggingStatus())
	{
		Asteroid newAsteroid = Asteroid(newAsteroid.SMALL);
		newAsteroid.ChangeDebuggingState();
		asteroids_.push_back(newAsteroid);
	}
	
}

//Deletes asteroids in debugging mode
void Game::DeleteAsteroidsInDebugging()
{
	if (asteroids_.size()>0)
		asteroids_.pop_back();
}

//Activates or disables the debugging mode
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

//Checks if two entities are colliding
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

int Game::GetAsteroidsNumber()
{
	return asteroids_.size();
}

//Manages the input keys for the game
void Game::GameInputManager()
{
	if (inputManger.GetKeyW())
	{
		player_.MoveForward();
		player_.SetMovingForwardState(true);
	}
	else
	{
		player_.SetMovingForwardState(false);
	}

	if(inputManger.GetKeyA())
	{
		player_.RotateLeft();
	}

	if (inputManger.GetKeyD())
	{
		player_.RotateRight();
	}
}

Player Game::GetPlayer()
{
	return player_;
}

void Game::PushDeltaTimeValues() 
{

	deltaTimePosition = 0;

	for (int i = 0; i < MAXIMUM_FRAME_CAPACITY; i++) {

		deltaTimeContainer_[i].x = i;
		deltaTimeContainer_[i].y = 0.0;
	}
}

void Game::UpdateDeltaTime(double deltaTime) 
{

	deltaTimeContainer_[deltaTimePosition] = Vector2((float)deltaTimePosition, deltaTime);

	deltaTimePosition++;

	if (deltaTimePosition >= MAXIMUM_FRAME_CAPACITY) {

		deltaTimePosition = 0;
	}
}

void Game::RenderFramePlot() 
{
	if(player_.GetDebuggingStatus())
		DrawFrameGraph();
}

void Game::DrawFrameGraph() 
{
	glColor3d(1.0, 1.0, 1.0);
	glLoadIdentity();
	glTranslatef(350.0f, -300.0f, 0.0f);

	//graphic axes
	glBegin(GL_LINE_STRIP);
	glVertex2d(0.0, 100.0);
	glVertex2d(0.0, 0.0);
	glVertex2d(200.0, 0.0);
	glEnd();

	glColor3d(orange.getRedValue(), orange.getGreenValue(), orange.getBlueValue());
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < MAXIMUM_FRAME_CAPACITY; i++) {

		glVertex2d(X_AXIS_SCALE * deltaTimeContainer_[i].x, Y_AXIS_SCALE * (DESIRED_FRAME_TIME - deltaTimeContainer_[i].y));
	}
	glEnd();
}
