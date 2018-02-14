#include "Player.hpp"
#include "Palette.h"
#include <cmath>
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	//Position of the player is set to origin
	position = Vector2(0, 0);
	//Controls if the ship is moving forward
	isMovingForward = false;
	//Frame data savers
	frameHeight = 0;
	frameWidth = 0;
	rotationAngle = 0;
	mathToools = MathUtilities();
}

Player::~Player()
{
}

void Player::Render()
{
	Palette colorPalette = Palette();
	Color background = colorPalette.getOrange();
	glClearColor(background.getRedValue(), background.getGreenValue(), background.getBlueValue(), background.getOpacityValue());
	glClear(GL_COLOR_BUFFER_BIT);

	drawShip();
}

void Player::drawShip()
{
	glLoadIdentity();
	glTranslated(position.x, position.y, 0.0);
	glRotated(rotationAngle, 0.0, 0.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f((0), (30));
	glVertex2f((20), (-15));
	glVertex2f((9), (-6));
	glVertex2f((-9), (-6));
	glVertex2f((-20), (-15));
	glEnd();

	//Controls if the thruster shows or not
	if (isMovingForward)
	{
		glBegin(GL_LINE_LOOP);
		glVertex2f((-9), (-6));
		glVertex2f((9), (-6));
		glVertex2f((0), (-18));
		glEnd();
	}
}



void Player::Move(Vector2 &moveValues)
{
	position.x += moveValues.x;
	position.y += moveValues.y;

	//Makes thae player ship appear in the opposite border when it reaches a border
	Warp(frameHeight, frameWidth);
}

void Player::MoveForward()
{
	double moveValue = 10;
	position.x -= moveValue * sin(mathToools.toRadians(rotationAngle));
	position.y += moveValue * cos(mathToools.toRadians(rotationAngle));

	Warp(frameHeight, frameWidth);
}

void Player::RotateLeft()
{
	rotationAngle += 15;
}

void Player::RotateRight()
{
	rotationAngle -= 15;
}

void Player::Warp(int frameHeight, int frameWidth)
{
	if (position.y > (frameHeight/2) || position.y < (-frameHeight / 2))
		position.y *= -1;

	if (position.x > (frameWidth / 2) || position.x < (-frameWidth / 2))
		position.x *= -1;
}

//changes if the key that makes the ship move forward is pressed
void Player::setMovingForwardState(bool isWPressed)
{
	isMovingForward = isWPressed;
}

//changes the value of the frame height and width
void Player::updateFrameData(int height, int width)
{
	frameHeight = height;
	frameWidth = width;
}

