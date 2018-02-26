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
	void ShootBullets();
	void PlayerCollision();
	void BulletCollision();
	void AddAsteroids();
	void DeleteAsteroids();
	void DebuggingModeToggle();
	bool CollidingDetection(Entity, Entity);
	void InputManager();

	bool GetKeyW();
	bool GetKeyA();
	bool GetKeyD();
	bool GetKeyF();
	bool GetKeyQ();
	bool GetKeyE();

	void SetKeyW();
	void SetKeyA();
	void SetKeyD();
	void SetKeyF();
	void SetKeyQ();
	void SetKeyE();

private:
	//Members
	Player player_;
	vector<Asteroid> asteroids_;
	vector<Ammo> playerBullets_;
	MathUtilities mathTools_;
	bool keyW;
	bool keyA;
	bool keyD;
	bool keyF;
	bool keyQ;
	bool keyE;
};

