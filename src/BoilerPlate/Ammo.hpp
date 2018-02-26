#pragma once
#include "Entity.hpp"

class Ammo : public Entity
{
public:
	Ammo(Entity);
	~Ammo();

	void Update(Entity, double);
	void Render() override;
	void DrawEntity() override;
	void EntityImpulse() override;
	void PushEntityVertices() override;
	void DebuggingHitBox() override;
	void BulletPosition();

	Entity player_;
	vector<Vector2> bulletContainer_;
	double bulletLife;
};

