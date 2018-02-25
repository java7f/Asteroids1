#include "Entity.hpp"



Entity::Entity()
{
	//Position of the player is set to origin
	//position_ = Vector2(0, 0);
	velocity_ = Vector2(0, 0);

	//Frame data savers
	frameHeight_ = 0;
	frameWidth_ = 0;

	mass_ = 0;
	rotationAngle = 0;
}


Entity::~Entity()
{
}

void Entity::Update(double deltaTime)
{
	position_.x += velocity_.x * static_cast<double>(deltaTime);
	position_.y += velocity_.y * static_cast<double>(deltaTime);

	Warp(frameHeight_, frameWidth_);
}

void Entity::Render()
{
	//To be implemented in the children classes
}

//Makes the entity appear on the opposite side of the screen if it reaches a border
void Entity::Warp(int frameHeight, int frameWidth)
{
	if (position_.x > (frameWidth))
		position_.x = -frameWidth;

	if (position_.x < -frameWidth)
		position_.x = frameWidth;


	if (position_.y > (frameHeight))
		position_.y = -frameHeight;

	if (position_.y < -frameHeight)
		position_.y = frameHeight;
}

void Entity::DrawEntity()
{
	//To be implemented in the children classes
}

//changes the value of the frame height and width
void Entity::UpdateFrameData(int height, int width)
{
	frameHeight_ = height/2;
	frameWidth_ = width/2;
}

void Entity::EntityImpulse()
{
}

void Entity::PushEntityVertices()
{
}
