#pragma once
/* A button class with colours and a texture*/
#include <SDL.h>

class Button
{
private:
	// Define texture to display
	SDL_Texture* mTexture;

	// Define background colour
	SDL_Color mBackground;

	// Top left position and dimensions of button and texture
	SDL_Rect mButtonRect;
	SDL_Rect mTextureRect;

public:
	// Constructor
	Button();

	// Set Texture
	void setTexture(SDL_Texture* texture);

	// Set button and center texture on button
	void setButtonRect(const SDL_Rect& rect);
	void centerTextureRect();

	// Check if mouse is inside button
	bool isMouseInside(const int x, const int y);

	// Set background colour
	void setBackground(SDL_Color colour);

	// Render background and texture
	void renderBackground(SDL_Renderer* renderer);
	void renderTexture(SDL_Renderer* renderer);

};