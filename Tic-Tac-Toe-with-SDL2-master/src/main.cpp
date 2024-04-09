/* Tic-Tac-Toe using SDL2 */
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "Button.h"

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 100;

const SDL_Color BLACK = { 0, 0, 0, 255 };
const SDL_Color WHITE = { 255, 255, 255, 255 };

const char* FONT_PATH = "VNARIAL.ttf";

// Define a player and state of a cell
static enum class State
{
	NONE,
	CROSS,
	CIRCLE,
};

// Each cell is a button and has a state
static struct Cell : Button
{
	State state;
	Cell() : state(State::NONE) {}
};

// Get index
inline int getIndex(const int cols, const int row, const int col)
{
	return cols * row + col;
}

// Load texture
SDL_Texture* loadTexture(SDL_Renderer* renderer, const char* filePath)
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* loadedSurface = nullptr;

	loadedSurface = SDL_LoadBMP(filePath);
	if (loadedSurface == nullptr)
	{
		std::cout << "SDL could not load texture! Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
		if (texture == nullptr)
		{
			std::cout << "SDL could not create texture from surface! Error: " << SDL_GetError() << std::endl;
		}
	}

	SDL_FreeSurface(loadedSurface);
	return texture;
}
SDL_Color yellow = { 255, 255, 0, 255 };
SDL_Color red = { 255, 0, 0, 255 };   
SDL_Color green = { 0, 255, 0, 255 };    
SDL_Color blue = { 0, 0, 255, 255 };      
SDL_Color white = { 255, 255, 255, 255 };  
SDL_Color black = { 0, 0, 0, 255 };
int toltalColor = 6;
SDL_Color myColor[] = { yellow , red ,green ,blue ,white ,black };
bool showYesNoMessageBox(SDL_Renderer* renderer, TTF_Font* font, Cell grid[], int cell[3], State winner) {
	SDL_Window* window = SDL_CreateWindow("Thong Bao", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
		return false;
	}


	SDL_Surface* surface = SDL_GetWindowSurface(window);

	SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 255, 255));
	const char* text;

	if (winner == State::NONE) {
		text = "Hoa nhau, ban co muon tiep tuc (Y/N)";
	}
	else if (winner == State::CROSS) {
		text = "Nguoi choi X thang, ban co muon tiep tuc (Y/N)";
	}
	else {
		text = "Nguoi choi O thang, ban co muon tiep tuc (Y/N)";
	}
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, BLACK);
	if (!textSurface) {
		std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
		return false;
	}

	SDL_Rect textRect;
	textRect.x = (WINDOW_WIDTH - textSurface->w) / 2;
	textRect.y = (WINDOW_HEIGHT - textSurface->h) / 2;
	textRect.w = textSurface->w;
	textRect.h = textSurface->h;

	SDL_BlitSurface(textSurface, nullptr, surface, &textRect);

	SDL_UpdateWindowSurface(window);

	bool quit = false;
	bool result = false;
	while (!quit) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_y) {
					quit = true;
					result = true;
				}
				else if (event.key.keysym.sym == SDLK_n) {
					quit = true;
					result = false;
				}
				break;
			}
		}
		if (winner == State::CIRCLE || winner == State::CROSS)
		{
			for (int c = 0; c < toltalColor; c++)
			{
				for (int i = 0; i < 3; i++)
				{
					grid[cell[i]].setBackground(myColor[c]);
					grid[cell[i]].setBackground(myColor[c]);
					grid[cell[i]].setBackground(myColor[c]);

					grid[cell[i]].renderBackground(renderer);
					grid[cell[i]].renderTexture(renderer);

				}
				SDL_RenderPresent(renderer);
				SDL_Delay(100);
			}
		}
	}

	SDL_DestroyWindow(window);
	return result;
}
int main(int argc, char* argcv[])
{
	// Define window dimensions
	const int windowWidth = 500;
	const int windowHeight = windowWidth;

	// Initalise SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL could not intialise! Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create window
	SDL_Window* window = SDL_CreateWindow("Tic-Tac-Toe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "SDL could not create window! Error: " << SDL_GetError() << std::endl;
		return -1;
	}

	// Create renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	if (renderer == nullptr)
	{
		std::cout << "SDL could not create renderer! Error: " << SDL_GetError() << std::endl;
		return -1;
	}
	if (TTF_Init() < 0)
	{
		std::cerr << "Failed to initialize SDL_ttf. Error: " << TTF_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	TTF_Font* font = TTF_OpenFont(FONT_PATH, 24);
	if (!font) {
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		TTF_Quit();
		SDL_Quit();
		return 1;
	}
	// Load textures for cross("X"), circle("O"), and an empty texture
	SDL_Texture* cross = loadTexture(renderer, "assets/Cross.bmp");
	SDL_Texture* circle = loadTexture(renderer, "assets/Circle.bmp");
	SDL_Texture* empty = loadTexture(renderer, "assets/Empty.bmp");

	// Create 3 x 3 grid of Cells
	const int rows = 3;
	const int cols = 3;
	const int totalCells = rows * cols;
	Cell grid[totalCells];

	// Define borders and thus dimensions of cells
	const int borderThickness = 10;
	const int buttonWidth = (windowWidth - 4 * borderThickness) / cols;
	const int buttonHeight = buttonWidth;

	// Set all cell starting positions, dimensions and state
	int cellStartY = borderThickness;
	for (int row = 0; row < rows; row++)
	{
		int cellStartX = borderThickness;
		for (int col = 0; col < cols; col++)
		{
			// Get index
			int index = getIndex(cols, row, col);

			// Set starting position and dimensions
			SDL_Rect rect = { cellStartX, cellStartY, buttonWidth, buttonHeight };
			grid[index].setButtonRect(rect);

			// Set to empty texture and center each texture onto button
			grid[index].setTexture(empty);
			grid[index].centerTextureRect();

			cellStartX += buttonWidth + borderThickness;
		}
		cellStartY += buttonHeight + borderThickness;
	}

	// Loop variables
	bool stop = false;
	SDL_Event event;
	State player = State::CIRCLE;
	State winner = State::NONE;
	int cellsFilled = 0;
	SDL_Color lightBlue = { 100, 171, 255, 255 };
	SDL_Color red = {255, 0, 0, 255};
	int indexWin[3] = { 0 };
	while (!stop)
	{
		// Handle events on queue
		while (SDL_PollEvent(&event) != 0)
		{
			// Handle quiting
			if (event.type == SDL_QUIT)
			{
				stop = true;
			}
			
			// If winner or no winner and all cells filled	
			if (winner == State::CIRCLE || winner == State::CROSS || (winner == State::NONE && cellsFilled == totalCells))
			{
				bool result = showYesNoMessageBox(renderer, font, grid, indexWin, winner);
				// Wait until another mouse down event to reset grid
				if (result == true)
				{
					// Clear
					for (int i = 0; i < totalCells; i++)
					{
						grid[i].state = State::NONE;
						grid[i].setTexture(empty);
						grid[i].setBackground({ 255,255,255,255 });
					}

					winner = State::NONE;
					cellsFilled = 0;
				}
				else
				{
					stop = true;
					break;
				}
			}
			// else no winner
			else
			{
				// Get mouse position and handle mouse events
				int x, y;
				SDL_GetMouseState(&x, &y);
				for (int i = 0; i < totalCells; i++)
				{
					// If cell is empty
					if (grid[i].state == State::NONE)
					{
						// If mouse down and inside the cell (Game logic)
						if (event.type == SDL_MOUSEBUTTONDOWN && grid[i].isMouseInside(x, y))
						{
							// Set state equal to state of player i.e. their symbol
							grid[i].state = player;
							cellsFilled++;

							// Set background colour for winning condition depending on winner
							SDL_Color background;
							if (player == State::CIRCLE) background = red;
							else background = lightBlue;
							
							/* CIRCLE */
							// Check each row
							if (grid[0].state == player && grid[1].state == player && grid[2].state == player)
							{
								grid[0].setBackground(background); 
								grid[1].setBackground(background); 
								grid[2].setBackground(background); 
								winner = player;
								indexWin[0] = 0;
								indexWin[1] = 1;
								indexWin[2] = 2;
							}
							if (grid[3].state == player && grid[4].state == player && grid[5].state == player) 
							{
								grid[3].setBackground(background); 
								grid[4].setBackground(background); 
								grid[5].setBackground(background); 
								indexWin[0] = 3;
								indexWin[1] = 4;
								indexWin[2] = 5;
								winner = player;
							}
							if (grid[6].state == player && grid[7].state == player && grid[8].state == player)
							{
								grid[6].setBackground(background); 
								grid[7].setBackground(background); 
								grid[8].setBackground(background); 
								indexWin[0] = 6;
								indexWin[1] = 7;
								indexWin[2] = 8;
								winner = player;
							}

							// Check each col
							if (grid[0].state == player && grid[3].state == player && grid[6].state == player)
							{
								grid[0].setBackground(background); 
								grid[3].setBackground(background); 
								grid[6].setBackground(background); 
								indexWin[0] = 0;
								indexWin[1] = 3;
								indexWin[2] = 6;
								winner = player;
							}
							if (grid[1].state == player && grid[4].state == player && grid[7].state == player) 
							{
								grid[1].setBackground(background); 
								grid[4].setBackground(background); 
								grid[7].setBackground(background);
								indexWin[0] = 1;
								indexWin[1] = 4;
								indexWin[2] = 7;
								winner = player;
							}
							if (grid[2].state == player && grid[5].state == player && grid[8].state == player) 
							{
								grid[2].setBackground(background); 
								grid[5].setBackground(background); 
								grid[8].setBackground(background); 
								indexWin[0] = 2;
								indexWin[1] = 5;
								indexWin[2] = 8;
								winner = player;
							}

							// Check diagonals
							if (grid[0].state == player && grid[4].state == player && grid[8].state == player)
							{
								grid[0].setBackground(background); 
								grid[4].setBackground(background); 
								grid[8].setBackground(background); 
								indexWin[0] = 0;
								indexWin[1] = 4;
								indexWin[2] = 8;
								winner = player;
							}
							if (grid[2].state == player && grid[4].state == player && grid[6].state == player) 
							{
								grid[2].setBackground(background); 
								grid[4].setBackground(background); 
								grid[6].setBackground(background); 
								indexWin[0] = 2;
								indexWin[1] = 4;
								indexWin[2] = 6;
								winner = player;
							}

							// Switch players and set textures
							if (player == State::CIRCLE)
							{
								// Set circle texture and switch player to cross
								grid[i].setTexture(circle);
								player = State::CROSS;
							}
							else
							{
								// Set cross texture and switch player to circle
								grid[i].setTexture(cross);
								player = State::CIRCLE;
							}
						}
					}
				}
			}
		}

		// Clear screen to colour of current player
		if (player == State::CIRCLE)
		{
			// Red
			SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		}
		else
		{
			// Light blue
			SDL_SetRenderDrawColor(renderer, 55, 171, 255, 255);
		}
		SDL_RenderClear(renderer);

		// Render background and texture of every button
		for (int i = 0; i < totalCells; i++)
		{
			grid[i].renderBackground(renderer);
			grid[i].renderTexture(renderer);
		}

		// Update screen from backbuffer and clear backbuffer
		SDL_RenderPresent(renderer);

		// Slow down program
		SDL_Delay(10);

	}

	// Free textures
	SDL_DestroyTexture(cross);
	SDL_DestroyTexture(circle);
	cross = nullptr;
	window = nullptr;

	// Destroy renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;

	// Quit
	SDL_Quit();

	return 0;
}