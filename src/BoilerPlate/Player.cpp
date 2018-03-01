#include "Player.hpp"
#include "Palette.hpp"
#include <cmath>
// OpenGL includes
#include <GL/glew.h>
#include <SDL_opengl.h>

const double MAX_SPEED = 300;
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
	isAlive = true;
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
	Color background = colorPalette.getBlack();
	glClearColor(background.getRedValue(), background.getGreenValue(), background.getBlueValue(), background.getOpacityValue());
	glClear(GL_COLOR_BUFFER_BIT);

	PushEntityVertices();

	if(isAlive)
	{
		DrawEntity();

		//Draws the hit box
		DebuggingHitBox();

		//Cleaning up the vectors 
		shipContainer_.clear();
		thrusterContainer_.clear();
	}
	else if (!isAlive && isDebugging_)
	{
		DrawEntity();
		DebuggingHitBox();
	}
}

//Hides the process of drawing the ship 
void Player::DrawEntity()
{
	glColor3d(1.0, 1.0, 1.0);
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
		glColor3d(1.0, 0.0, 0.0);
		glBegin(GL_POLYGON);
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
	rotationAngle += 5;
}

//Minimizes the rotation angle
void Player::RotateRight()
{
	rotationAngle -= 5;
}

//changes if the key that makes the ship move forward is pressed
void Player::SetMovingForwardState(bool isWPressed)
{
	isMovingForward = isWPressed;
}

//Increments velocity
void Player::EntityImpulse()
{
	if (mass_ > 0) 
	{
		velocity_.x -= (moveValue / mass_) * sin(mathTools_.ToRadians(rotationAngle));
		velocity_.y += (moveValue / mass_) * cos(mathTools_.ToRadians(rotationAngle));
	}
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
	if (isDebugging_) 
	{
		int numbersOfLines = 500;
		glColor3d(1.0, 1.0, 1.0);
		glLoadIdentity();
		glBegin(GL_LINE_LOOP);
		for (int i = 0; i <= numbersOfLines; i++)
		{
			glVertex2d(position_.x + (radius_ * cos(i *  (2 * mathTools_.PI / numbersOfLines))), position_.y + (radius_* sin(i * 2 * mathTools_.PI / numbersOfLines)));
		}
		glEnd();
	}
}

void Player::PlayerRespawn()
{
	position_ = Vector2(0, 0);
	velocity_ = Vector2(0, 0);
	isAlive = true;
}

int Player::GetHeight()
{
	return frameHeight_;
}

int Player::GetWidth()
{
	return frameWidth_;
}



