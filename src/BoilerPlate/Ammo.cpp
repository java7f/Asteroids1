#include "Ammo.hpp"

Ammo::Ammo(Entity player)
{
	Entity();
	player_ = player;
	BulletPosition();
	moveValue = 300;
	mass_ = 0.50;
	radius_ = 6;
	bulletLife_ = 100;
}


Ammo::~Ammo()
{
}

void Ammo::Update(Entity player, double deltaTime)
{
	EntityImpulse();
	//Controlling the life of the bullet
	bulletLife_--;
	if (bulletLife_ <= 0)
	{
		isAlive = false;
	}
	Entity::Update(deltaTime);
}

void Ammo::Render()
{
	PushEntityVertices();
	DrawEntity();

	//Decides if the hit box shows or not
	if (isDebugging_)
		DebuggingHitBox();

	//Cleaning the container
	bulletContainer_.clear();
}

//Draws the bullet
void Ammo::DrawEntity()
{
	glLoadIdentity();
	glTranslated(position_.x, position_.y, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < bulletContainer_.size(); i++)
	{
		glVertex2d((bulletContainer_.at(i).x), (bulletContainer_.at(i).y));
	}
	glEnd();
}

//Makes the bullet move
void Ammo::EntityImpulse()
{
	if (mass_ > 0)
	{
		velocity_.x = (moveValue / mass_) * -sin(mathTools_.ToRadians(player_.GetRotationAngle()));
		velocity_.y = (moveValue / mass_) * cos(mathTools_.ToRadians(player_.GetRotationAngle()));
	}
}

//Saves the bullet vertices
void Ammo::PushEntityVertices()
{
	bulletContainer_.push_back(Vector2(-5, 0));
	bulletContainer_.push_back(Vector2(5, 0));
	bulletContainer_.push_back(Vector2(0, 8));
}

//Draws the hit box in debugging
void Ammo::DebuggingHitBox()
{
	int numbersOfLines = 500;
	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= numbersOfLines; i++)
	{
		glVertex2d(position_.x + (radius_ * cos(i *  (2 * mathTools_.PI / numbersOfLines))), position_.y + (radius_* sin(i * 2 * mathTools_.PI / numbersOfLines)));
	}
	glEnd();
}

//Moves the bullet initial position according to the ship orientation
void Ammo::BulletPosition()
{
	position_.x = player_.GetPosition().x + (player_.GetRadius() * -sin(mathTools_.ToRadians(player_.GetRotationAngle())));
	position_.y = player_.GetPosition().y + (player_.GetRadius() * cos(mathTools_.ToRadians(player_.GetRotationAngle())));
}