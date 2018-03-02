#pragma once
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Ammo.hpp"
#include "InputManager.hpp"
#include "Color.hpp"
#include "Palette.hpp"
#include "DisplayText.hpp"
#include <irrKlang.h>
#include <iostream>

const double DESIRED_FRAME_RATE = 60.0;
const double DESIRED_FRAME_TIME = 1.0 / DESIRED_FRAME_RATE;
const double X_AXIS_SCALE = 15.0;
const double Y_AXIS_SCALE = 100000.0;
const double LIVES_X_POSITION = 200;
const double LIVES_Y_POSITION = 40;
const double SCORE_X_POSITION = 200;
const double SCORE_Y_POSITION = 110;
const int SCORE_FONT_SIZE = 50;
const int RESET_FONT_SIZE = 100;
const int MAXIMUM_FRAME_CAPACITY= 15;
const int INITIAL_ASTEROIDS = 4;
const int INITIAL_LIVES = 3;
const int INCREASE_LIFE_FACTOR = 2000;
const int ORIGIN = 0;
const int MESSAGES_X_POSITION = -100;
const int MESSAGES_Y_POSITION = 100;
const int RESET_IMMORTAL_TIME = 150;


class Game
{
public:

	//Constructor
	Game();
	~Game();

	//Functions
	void RenderGame();
	void RenderLives();
	void RenderPlayerScore();
	void RenderResetGame();
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
	void RespawnTilting();
	void ResetGame();
	void FontColor(int, int, int, int);
	bool CollidingDetection(Entity, Entity);
	int GetAsteroidsNumber();
	DisplayText GetFont();
	Player GetPlayer();
	InputManager inputManger;
	DisplayText *gameFont_;
	SDL_Color fontColor_;
	//Delta time functions
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
	double livesPositionX, livesPositionY;
	double scorePositionX, scorePositionY;
	int messagesPositionX, messagesPositionY;
	int livesRenderMovement;
	int deltaTimePosition;
	int roundCounter;
	int additionalLiveFactor;
	int immortalityTime;
	bool isRespawning;
	bool ifCollision;
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

