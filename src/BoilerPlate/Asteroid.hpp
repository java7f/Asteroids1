#pragma once
#include "MathUtilities.h"
#include "Entity.hpp"

class Asteroid : public Entity
{
public:

	enum AsteroidSize
	{
		SMALL = 1,
		MEDIUM = 2,
		BIG = 3,
	};

	Asteroid(AsteroidSize size);
	~Asteroid();

	//Public functions
	void Update() override;
	void Render() override;
	void drawEntity() override;

private:
	//Attributes
	AsteroidSize size_;
	vector<Vector2> asteroidContainer_;
};

