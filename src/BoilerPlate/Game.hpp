#pragma once
#include "Player.hpp"
#include "Asteroid.hpp"
#include "Ammo.hpp"
#include <iostream>
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
	void PushAsteroids();
	void AddBullets();
	void PlayerCollision();
	void BulletCollision();
	void AddAsteroids();
	void DeleteAsteroids();
	void DebuggingModeToggle();


	//Members
	Player player_;
	vector<Asteroid> asteroids_;
	vector<Ammo> playerBullets_;
	MathUtilities mathTools_;
};

