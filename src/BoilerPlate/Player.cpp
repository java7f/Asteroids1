#include "Player.hpp"
#include "Palette.h"
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
	mathToools_ = MathUtilities();

	
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Render()
{
	Palette colorPalette = Palette();
	Color background = colorPalette.getOrange();
	glClearColor(background.getRedValue(), background.getGreenValue(), background.getBlueValue(), background.getOpacityValue());
	glClear(GL_COLOR_BUFFER_BIT);

	drawEntity();
}

void Player::drawEntity()
{
	shipContainer_.push_back(Vector2(0, 30));
	shipContainer_.push_back(Vector2(20, -15));
	shipContainer_.push_back(Vector2(9, -6));
	shipContainer_.push_back(Vector2(-9, -6));
	shipContainer_.push_back(Vector2(-20, -15));

	thrusterContainer_.push_back(Vector2(-9, -6));
	thrusterContainer_.push_back(Vector2(9, -6));
	thrusterContainer_.push_back(Vector2(0, -18));

	glLoadIdentity();
	glTranslated(position_.x, position_.y, 0.0);
	glRotated(rotationAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < shipContainer_.size(); i++)
	{
		glVertex2f((shipContainer_.at(i).x), (shipContainer_.at(i).y));
	}
	glEnd();

	//Controls if the thruster shows or not
	if (isMovingForward)
	{
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i < thrusterContainer_.size(); i++)
		{
			glVertex2f((thrusterContainer_.at(i).x), (thrusterContainer_.at(i).y));
		}
		glEnd();
	}
}


void Player::MoveForward()
{
	double moveValue = 10;
	position_.x -= moveValue * sin(mathToools_.toRadians(rotationAngle));
	position_.y += moveValue * cos(mathToools_.toRadians(rotationAngle));

	Warp(frameHeight_, frameWidth_);
}

void Player::RotateLeft()
{
	rotationAngle += 15;
}

void Player::RotateRight()
{
	rotationAngle -= 15;
}

//changes if the key that makes the ship move forward is pressed
void Player::setMovingForwardState(bool isWPressed)
{
	isMovingForward = isWPressed;
}

//changes the value of the frame height and width
void Player::updateFrameData(int height, int width)
{
	frameHeight_ = height;
	frameWidth_ = width;
}

