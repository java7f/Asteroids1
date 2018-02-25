#pragma once
#include "Player.hpp"
#include "Asteroid.hpp"
class Game
{
public:

	Game();
	~Game();

	void RenderGame();
	void UpdateGame(double, double, double);
	void DebuggingLine();
	void PushAsteroids();

	//Members
	Player player;
	vector<Asteroid> asteroids;
};

