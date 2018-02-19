#pragma once
#include "Entity.hpp"
#include "MathUtilities.h"
class Player : public Entity
{
public:

	//Constructors
	Player();
	~Player();

	//Public functions
	void Update() override;
	void Render() override;
	void drawEntity() override;
	void MoveForward();
	void RotateLeft();
	void RotateRight();
	void setMovingForwardState(bool);
	void updateFrameData(int, int);

private:
	vector<Vector2> shipContainer_;
	vector<Vector2> thrusterContainer_;
	MathUtilities mathToools_;

	bool isMovingForward;
	double rotationAngle;
};

