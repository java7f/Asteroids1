#pragma once
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Ammo.hpp"
#include "InputManager.hpp"
#include "Color.hpp"
#include "Palette.hpp"
#include <irrKlang.h>
#include <iostream>

const double DESIRED_FRAME_RATE = 60.0;
const double DESIRED_FRAME_TIME = 1.0 / DESIRED_FRAME_RATE;
const double X_AXIS_SCALE = 15.0;
const double Y_AXIS_SCALE = 100000.0;
const int MAXIMUM_FRAME_CAPACITY= 15;
const int INITIAL_ASTEROIDS = 4;
const int LIVES_X_POSITION = 200;
const int LIVES_Y_POSITION = 40;
const int INCREASE_LIFE_FACTOR = 1000;

class Game
{
public:

	//Constructor
	Game();
	~Game();

	//Functions
	void RenderGame();
	void RenderLives();
	void UpdateGame(double, double, double);
	void DebuggingLine();
	void PushAsteroidsPerRound();
	void ShootBullets();
	void PlayerCollision();
	void BulletCollision();
	void AddAsteroidsInDebugging();
	void DeleteAsteroidsInDebugging();
	void DebuggingModeToggle();
	void GameInputManager();
	void RespawnPlayer();
	void PushShipLivesVertices();
	void IncreaseLivesPerScore();
	bool CollidingDetection(Entity, Entity);
	int GetAsteroidsNumber();
	Player GetPlayer();
	InputManager inputManger;

	void PushDeltaTimeValues();
	void UpdateDeltaTime(double);
	void RenderFramePlot();
	void DrawFrameGraph();


	//Global variables
	double radiusForMeasurement;
	double distanceToAsteroid;
	double shipX, shipY;
	double asteroidX, asteroidY;
	double bulletX, bulletY;
	double frameHeight, frameWidth;
	int livesPositionX, livesPositionY;
	int livesRenderMovement;
	int deltaTimePosition;
	int roundCounter;
	int additionalLiveFactor;
	Palette graphColor;
	Color orange;

private:

	//Members
	Player player_;
	std::vector<Asteroid> asteroids_;
	std::vector<Ammo> playerBullets_;
	std::vector<Vector2> deltaTimeContainer_;
	std::vector<Vector2> livesShipContainer_;
	irrklang::ISoundEngine* soundEngine_;
	MathUtilities mathTools_;
	int playerLives_;
	int playerScore_;
};

