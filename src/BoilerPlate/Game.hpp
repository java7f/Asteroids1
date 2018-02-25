#pragma once
#include "Player.hpp"
#include "Asteroid.hpp"
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

	//Members
	Player player_;
	vector<Asteroid> asteroids_;
	MathUtilities mathTools_;
};

