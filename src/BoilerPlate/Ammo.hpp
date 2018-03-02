#pragma once
#include "Entity.hpp"

class Ammo : public Entity
{
public:
	//Constructors
	Ammo(Entity);
	~Ammo();

	//Functions
	void Update(Entity, double);
	void Render() override;
	void DrawEntity() override;
	void EntityImpulse() override;
	void PushEntityVertices() override;
	void DebuggingHitBox() override;
	void BulletPosition();

	//Members
	Entity player_;
	std::vector<Vector2> bulletContainer_;
	double bulletLife_;
};

