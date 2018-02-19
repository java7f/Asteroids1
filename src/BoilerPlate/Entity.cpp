#include "Entity.hpp"



Entity::Entity()
{
	//Position of the player is set to origin
	position_ = Vector2(0, 0);
	//Frame data savers
	frameHeight_ = 0;
	frameWidth_ = 0;

	mass_ = 0;
}


Entity::~Entity()
{
}

void Entity::Update()
{
	//To be implemented later
}

void Entity::Render()
{
	//To be implemented in the children classes
}

//Makes the entity appear on the opposite side of the screen if it reaches a border
void Entity::Warp(int frameHeight, int frameWidth)
{
	if (position_.y > (frameHeight / 2) || position_.y < (-frameHeight / 2))
		position_.y *= -1;

	if (position_.x >(frameWidth / 2) || position_.x < (-frameWidth / 2))
		position_.x *= -1;
}

void Entity::DrawEntity()
{
	//To be implemented in the children classes
}

//changes the value of the frame height and width
void Entity::UpdateFrameData(int height, int width)
{
	frameHeight_ = height;
	frameWidth_ = width;
}
