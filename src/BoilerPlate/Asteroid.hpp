#pragma once
#include "MathUtilities.hpp"
#include "Entity.hpp"

class Asteroid : public Entity
{
public:

	//Controls the sizes that can be applied to the ship
	enum AsteroidSize
	{
		SMALL = 1,
		MEDIUM = 2,
		BIG = 3,
	};

	//Constructors
	Asteroid(AsteroidSize size);
	~Asteroid();

	//Public functions
	void Update() override;
	void Render() override;
	void DrawEntity() override;
	AsteroidSize getSize();

private:
	//Members
	AsteroidSize size_;
	vector<Vector2> asteroidContainer_;
};

