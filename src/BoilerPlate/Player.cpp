#include "Player.hpp"
#include "Palette.hpp"
#include <cmath>
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	Entity();
	//Controls if the ship is moving forward
	isMovingForward = false;
	rotationAngle = 0;
	mass_ = 0.98;
	mathTools_ = MathUtilities();
}

Player::~Player()
{
}

void Player::Update(double deltaTime)
{
	double speed = velocity_.Module();
	if (!isMovingForward)
	{
		velocity_ *= 0.98;
	}

	if (speed >= 500)
	{
		velocity_.x = (velocity_.x / speed) * 500;
		velocity_.y = (velocity_.y / speed) * 500;
	}

	Entity::Update(deltaTime);
}

void Player::Render()
{
	Palette colorPalette = Palette();
	Color background = colorPalette.getPurple();
	glClearColor(background.getRedValue(), background.getGreenValue(), background.getBlueValue(), background.getOpacityValue());
	glClear(GL_COLOR_BUFFER_BIT);

	PushEntityVertices();
	DrawEntity();
	shipContainer_.clear();
	thrusterContainer_.clear();
}

//Hides the process of drawing the ship and saves the ship and thruster points
void Player::DrawEntity()
{

	glLoadIdentity();
	glTranslated(position_.x, position_.y, 0.0);
	glRotated(rotationAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < shipContainer_.size(); i++)
	{
		glVertex2d((shipContainer_.at(i).x), (shipContainer_.at(i).y));
	}
	glEnd();

	//Controls if the thruster shows or not
	if (isMovingForward)
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < thrusterContainer_.size(); i++)
		{
			glVertex2d((thrusterContainer_.at(i).x), (thrusterContainer_.at(i).y));
		}
		glEnd();
	}
}


//Makes the ship move to where is pointing
void Player::MoveForward()
{
	EntityImpulse();
	//Warp(frameHeight_, frameWidth_);
}

//Increments the rotation angle
void Player::RotateLeft()
{
	rotationAngle += 15;
}

//Minimizes the rotation angle
void Player::RotateRight()
{
	rotationAngle -= 15;
}

//changes if the key that makes the ship move forward is pressed
void Player::SetMovingForwardState(bool isWPressed)
{
	isMovingForward = isWPressed;
}

void Player::EntityImpulse()
{
	double moveValue = 10;
	velocity_.x -= (moveValue/mass_) * sin(mathTools_.ToRadians(rotationAngle));
	velocity_.y += (moveValue/mass_) * cos(mathTools_.ToRadians(rotationAngle));
}

void Player::PushEntityVertices()
{
	shipContainer_.push_back(Vector2(0, 30));
	shipContainer_.push_back(Vector2(20, -15));
	shipContainer_.push_back(Vector2(9, -6));
	shipContainer_.push_back(Vector2(-9, -6));
	shipContainer_.push_back(Vector2(-20, -15));

	thrusterContainer_.push_back(Vector2(-9, -6));
	thrusterContainer_.push_back(Vector2(9, -6));
	thrusterContainer_.push_back(Vector2(0, -18));
}


