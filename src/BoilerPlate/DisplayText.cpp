#include "DisplayText.hpp"



DisplayText::DisplayText(double height, double width, int size)
{
	InitializeFont();
	gameFont_ = TTF_OpenFont("fonts/font.ttf", size);
	frameHeight_ = height;
	frameWidht_ = width;
}

DisplayText::~DisplayText()
{

}

bool DisplayText::InitializeFont()
{
	if (TTF_Init() == -1) {
		SDL_Log("TTF_Init: %s\n", TTF_GetError());
		return false;
	}
}

void DisplayText::CleanUp()
{
	TTF_Quit();
}

void DisplayText::FontRender(std::string message, SDL_Color color, float x, float y, int size) 
{

	glLoadIdentity();
	glTranslatef(x, y, 0.f);

	SDL_Surface *surface;

	//Render font to a SDL_Surface
	if ((surface = TTF_RenderText_Blended(gameFont_, message.c_str(), color)) == nullptr) {
		TTF_CloseFont(gameFont_);
		std::cout << "TTF_RenderText error: " << std::endl;
		return;
	}

	GLuint texId;

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Find the first power of two for OpenGL image 
	int w = PowerOfTwo(surface->w) * 2;
	int h = PowerOfTwo(surface->h) * 2;

	//Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(surface, NULL, s, NULL);

	//Copy the created image into OpenGL format
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);

	//Draw the OpenGL texture as a Quad
	glBegin(GL_QUADS); {
		glTexCoord2d(0, 1); glVertex3f(0, 0, 0);
		glTexCoord2d(1, 1); glVertex3f(0 + surface->w, 0, 0);
		glTexCoord2d(1, 0); glVertex3f(0 + surface->w, 0 + surface->h, 0);
		glTexCoord2d(0, 0); glVertex3f(0, 0 + surface->h, 0);
	} glEnd();
	glDisable(GL_TEXTURE_2D);

	//Cleanup
	SDL_FreeSurface(s);
	SDL_FreeSurface(surface);
	glDeleteTextures(1, &texId);
}

unsigned int DisplayText::PowerOfTwo(unsigned int val)
{
	unsigned int power = 2, nextVal = power * 2;
	while ((nextVal *= 2) <= val)
		power *= 2;
	return power * 2;
}
