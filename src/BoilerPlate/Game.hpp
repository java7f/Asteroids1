#pragma once
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Ammo.hpp"
#include "InputManager.hpp"
#include "Color.hpp"
#include "Palette.hpp"
#include <iostream>

const double DESIRED_FRAME_RATE = 60.0;
const double DESIRED_FRAME_TIME = 1.0 / DESIRED_FRAME_RATE;
const double X_AXIS_SCALE = 15.0;
const double Y_AXIS_SCALE = 100000.0;
const int MAXIMUM_FRAME_CAPACITY= 15;
const int INITIAL_ASTEROIDS = 5;

class Game
{
public:

	//Constructor
	Game();
	~Game();

	//Functions
	void RenderGame();
	void UpdateGame(double, double, double);
	void DebuggingLine();
	void PushAsteroidsPerRound();
	void ShootBullets();
	void PlayerCollision();
	void BulletCollision();
	void AddAsteroidsInDebugging();
	void DeleteAsteroidsInDebugging();
	void DebuggingModeToggle();
	bool CollidingDetection(Entity, Entity);
	int GetAsteroidsNumber();
	void GameInputManager();
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
	int deltaTimePosition;
	int roundCounter;
	Palette graphColor;
	Color orange;

private:

	//Members
	Player player_;
	std::vector<Asteroid> asteroids_;
	std::vector<Ammo> playerBullets_;
	std::vector<Vector2> deltaTimeContainer_;
	MathUtilities mathTools_;
	int playerLives_;
};

