#include "Button.h"

Button::Button()
	: mTexture(nullptr),
	  mBackground({255, 255, 255, 255}),
	  mButtonRect({ 0, 0, 0, 0 }),
	  mTextureRect({ 0, 0, 0, 0 })
{

}

void Button::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
}

void Button::setButtonRect(const SDL_Rect& rect)
{
	mButtonRect = rect;
}

void Button::centerTextureRect()
{
	int textureWidth;
	int textureHeight;
	SDL_QueryTexture(mTexture, NULL, NULL, &textureWidth, &textureHeight);

	const int textureStartRow = mButtonRect.y + 0.5 * (mButtonRect.h - textureHeight);
	const int textureStartCol = mButtonRect.x + 0.5 * (mButtonRect.w - textureWidth);

	mTextureRect = { textureStartCol, textureStartRow, textureWidth, textureHeight };
}

bool Button::isMouseInside(const int x, const int y)
{
	// Check if mouse is in button
	bool inside = true;

	// Mouse is left of the button
	if (x < mButtonRect.x)
	{
		inside = false;
	}
	// Mouse is right of the button
	else if (x > mButtonRect.x + mButtonRect.w)
	{
		inside = false;
	}
	// Mouse above the button
	else if (y < mButtonRect.y)
	{
		inside = false;
	}
	// Mouse below the button
	else if (y > mButtonRect.y + mButtonRect.h)
	{
		inside = false;
	}

	return inside;
}

void Button::setBackground(SDL_Color colour)
{
	mBackground = colour;
}


void Button::renderBackground(SDL_Renderer* renderer)
{
	// Set rendering colour for background
	SDL_SetRenderDrawColor(renderer, mBackground.r, mBackground.g, mBackground.b, mBackground.a);
	SDL_RenderFillRect(renderer, &mButtonRect);
}

void Button::renderTexture(SDL_Renderer* renderer)
{
	// Set rendering space
	SDL_RenderCopy(renderer, mTexture, nullptr, &mTextureRect);
}

