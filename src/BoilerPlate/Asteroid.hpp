#pragma once
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
	Asteroid(AsteroidSize);
	~Asteroid();

	//Public functions
	void Update(double) override;
	void Render() override;
	void DrawEntity() override;
	void EntityImpulse() override;
	void PushEntityVertices() override;
	AsteroidSize getSize();

private:
	//Members
	AsteroidSize size_;
	vector<Vector2> asteroidContainer_;
	double rotationFactor;
};

