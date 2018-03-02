#include "Game.hpp"
#include <string>

Game::Game()
{
	PushShipLivesVertices();
	player_ = Player();
	PushAsteroidsPerRound();
	mathTools_ = MathUtilities();
	graphColor = Palette();
	orange = graphColor.getOrange();
	deltaTimeContainer_ = std::vector<Vector2>(MAXIMUM_FRAME_CAPACITY);
	soundEngine_ = irrklang::createIrrKlangDevice();
	PushDeltaTimeValues();
	playerLives_ = INITIAL_LIVES; 
	playerScore_ = 0;
	roundCounter = 0;
	livesRenderMovement = 0;
	additionalLiveFactor = 2000;
	gameFont_ = new DisplayText(frameHeight, frameWidth, SCORE_FONT_SIZE);
	gameFont_->InitializeFont();
}


Game::~Game()
{
}

void Game::RenderGame()
{
	//Rendering the entities of the game
	player_.Render();
	RenderLives();

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
	RenderPlayerScore();
	RenderResetGame();
}

void Game::RenderLives()
{
	livesRenderMovement = 0;
	for (int i = 0; i < playerLives_; i++)
	{
		livesPositionX = frameWidth - LIVES_X_POSITION + livesRenderMovement;
		livesPositionY = frameHeight - LIVES_Y_POSITION;
		glLoadIdentity();
		glTranslated(livesPositionX, livesPositionY, 0.0);
		glColor3d(1.0, 1.0, 1.0);
		glBegin(GL_POLYGON);
		for (int j = 0; j < livesShipContainer_.size(); j++)
		{
			glVertex2d((livesShipContainer_.at(j).x), (livesShipContainer_.at(j).y));
		}
		glEnd();
		livesRenderMovement += 25;
	}
	
}

void Game::RenderPlayerScore()
{
	scorePositionX = frameWidth - SCORE_X_POSITION;
	scorePositionY = frameHeight - SCORE_Y_POSITION;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gameFont_->FontRender(std::to_string(playerScore_),fontColor_, scorePositionX, scorePositionY, SCORE_FONT_SIZE);
}

void Game::RenderResetGame()
{
	if (playerLives_ == 0) 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		gameFont_->FontRender("You lost!", fontColor_, MESSAGES_X_POSITION, MESSAGES_Y_POSITION, RESET_FONT_SIZE);
		gameFont_->FontRender("Press R to restart the game.", fontColor_, MESSAGES_X_POSITION - 140, ORIGIN, RESET_FONT_SIZE);
	}
}

void Game::UpdateGame(double deltaTime, double m_height, double m_width)
{
	frameHeight = m_height/2;
	frameWidth = m_width/2;
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
		roundCounter++;
		PushAsteroidsPerRound();
	}

	IncreaseLivesPerScore();

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

		glLoadIdentity();
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
		soundEngine_->play2D("sounds/fire.wav");
	}
}

//Controls the collision between the ship and asteroids
void Game::PlayerCollision()
{
	for (int i = 0; i < asteroids_.size(); i++)
	{
		if (CollidingDetection(player_, asteroids_[i]) && !player_.GetDebuggingStatus() && playerLives_ > 0)
		{
			playerLives_--;
			player_.SetAliveState(false);
			player_.PlayerRespawn();
			soundEngine_->play2D("sounds/saucerBig.wav");
		}

		if (playerLives_ == 0 && !player_.GetDebuggingStatus())
		{
			player_.SetAliveState(false);
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
						soundEngine_->play2D("sounds/bangLarge.wav");
						playerScore_ += 10;
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
						soundEngine_->play2D("sounds/bangMedium.wav");
						playerScore_ += 20;
						ifCollision = true;
					}
					else
					{
						asteroids_.erase(asteroids_.begin() + i);
						playerBullets_.erase(playerBullets_.begin() + j);
						soundEngine_->play2D("sounds/bangSmall.wav");
						playerScore_ += 40;
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
		Asteroid newAsteroid = Asteroid(newAsteroid.BIG);
		newAsteroid.ChangeDebuggingState();
		asteroids_.push_back(newAsteroid);
	}
	
}

//Deletes asteroids in debugging mode
void Game::DeleteAsteroidsInDebugging()
{
	if (asteroids_.size() > 0)
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

DisplayText Game::GetFont()
{
	return *gameFont_;
}

//Manages the input keys for the game
void Game::GameInputManager()
{
	if (inputManger.GetKeyW())
	{
		player_.MoveForward();
		player_.SetMovingForwardState(true);
		if(player_.GetAliveStatus())
			soundEngine_->play2D("sounds/thrust.wav");
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

void Game::RespawnPlayer()
{
	if (!player_.GetAliveStatus() && playerLives_ != 0)
	{
		player_.PlayerRespawn();
	}
}

void Game::PushShipLivesVertices()
{
	livesShipContainer_.push_back(Vector2(0, 15));
	livesShipContainer_.push_back(Vector2(10, -7.5));
	livesShipContainer_.push_back(Vector2(4.5, -3));
	livesShipContainer_.push_back(Vector2(-4.5, -3));
	livesShipContainer_.push_back(Vector2(-10, -7.5));
}

void Game::IncreaseLivesPerScore()
{
	if (playerScore_ - additionalLiveFactor >= 0)
	{
		playerLives_++;
		additionalLiveFactor += INCREASE_LIFE_FACTOR;
		soundEngine_->play2D("sounds/extraShip.wav");
	}
}

void Game::ResetGame()
{
	if (playerLives_ == 0)
	{
		asteroids_.clear();
		PushAsteroidsPerRound();
		playerLives_ = INITIAL_LIVES;
		player_.PlayerRespawn();
		roundCounter = 0;
		playerScore_ = 0;
		additionalLiveFactor = INCREASE_LIFE_FACTOR;
		if (player_.GetDebuggingStatus())
			player_.ChangeDebuggingState();
	}
}

void Game::FontColor(int red, int green, int blue, int alpha)
{
	fontColor_.r = red;
	fontColor_.g = green;
	fontColor_.b = blue;
	fontColor_.a = alpha;
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
