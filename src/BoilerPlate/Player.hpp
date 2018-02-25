#pragma once
#include "Entity.hpp"
class Player : public Entity
{
public:

	//Constructors
	Player();
	~Player();

	//Public functions
	void Update(double) override;
	void Render() override;
	void DrawEntity() override;
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void SetMovingForwardState(bool);
	void EntityImpulse() override;
	void PushEntityVertices() override;
	void DebuggingHitBox() override;

private:
	//Members
	vector<Vector2> shipContainer_;
	vector<Vector2> thrusterContainer_;

	//Attributes
	bool isMovingForward;
};

