#include "Player.hpp"
#include "Palette.hpp"
#include <cmath>
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

const double MAX_SPEED = 500;
const double FRICTION = 0.98;

Player::Player()
{
	Entity();

	//Controls if the ship is moving forward
	isMovingForward = false;

	rotationAngle = 0;
	mass_ = 1;
	radius_ = 25;
	mathTools_ = MathUtilities();

	moveValue = 10;
}

Player::~Player()
{
}

void Player::Update(double deltaTime)
{
	double speed = velocity_.Module();

	//If is not moving, makes it stop 
	if (!isMovingForward)
	{
		velocity_ *= FRICTION;
	}

	//Controlling the max speed of the ship
	if (speed >= MAX_SPEED)
	{
		velocity_.x = (velocity_.x / speed) * MAX_SPEED;
		velocity_.y = (velocity_.y / speed) * MAX_SPEED;
	}

	Entity::Update(deltaTime);
}

void Player::Render()
{
	Palette colorPalette = Palette();
	Color background = colorPalette.getMaroon();
	glClearColor(background.getRedValue(), background.getGreenValue(), background.getBlueValue(), background.getOpacityValue());
	glClear(GL_COLOR_BUFFER_BIT);

	PushEntityVertices();
	DrawEntity();

	//Decides id the hit box shows or not
	if(isDebugging_)
		DebuggingHitBox();

	//Cleaning up the vectors 
	shipContainer_.clear();
	thrusterContainer_.clear();
}

//Hides the process of drawing the ship 
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

//Increments velocity
void Player::EntityImpulse()
{
	velocity_.x -= (moveValue/mass_) * sin(mathTools_.ToRadians(rotationAngle));
	velocity_.y += (moveValue/mass_) * cos(mathTools_.ToRadians(rotationAngle));
}

//Saves the ship and the thruster data
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

//Draws the hit box 
void Player::DebuggingHitBox()
{
	int numbersOfLines = 500;
	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= numbersOfLines; i++) 
	{
		glVertex2d(position_.x + (radius_ * cos(i *  (2*mathTools_.PI / numbersOfLines))), position_.y + (radius_* sin(i * 2*mathTools_.PI / numbersOfLines)));
	}
	glEnd();
}



