#pragma once
#include "Entity.hpp"
#include "MathUtilities.hpp"
class Player : public Entity
{
public:

	//Constructors
	Player();
	~Player();

	//Public functions
	void Update() override;
	void Render() override;
	void DrawEntity() override;
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void SetMovingForwardState(bool);

private:
	//Members
	vector<Vector2> shipContainer_;
	vector<Vector2> thrusterContainer_;
	MathUtilities mathToools_;

	//Attributes
	bool isMovingForward;
	double rotationAngle;
};

