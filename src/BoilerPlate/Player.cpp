#include "Player.hpp"
#include "Palette.h"
// OpenGL includes
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player()
{
	position = Vector2(0, 0);
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


	/*0, 20
12, -10
6, -4
-6, -4
-12, -10*/
	glBegin(GL_LINE_LOOP);
	glVertex2f((0 + position.x), (20 + position.y));
	glVertex2f((12 + position.x), (-10 + position.y));
	glVertex2f((6 + position.x), (-4 + position.y));
	glVertex2f((-6 + position.x), (-4 + position.y));
	glVertex2f((-12 + position.x), (-10 + position.y));
	glEnd();
}

void Player::Move(Vector2 &moveValues)
{
	position.x += moveValues.x;
	position.y += moveValues.y;
}
