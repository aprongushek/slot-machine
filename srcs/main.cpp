#include <iostream>

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

#include "textures.h"
#include "drum.h"
#include "button.h"
#include "game.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define DRUMSET_X 90
#define DRUMSET_Y 140

#define BUTTONS_Y 395
#define START_BUTTON_X 90
#define STOP_BUTTON_X 420

#define MINFRAMETIME 17

int main () 
{
	SDL_SetMainReady();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *win = SDL_CreateWindow("SLOT", 
	                                   100, 100, 
	                                   SCREEN_WIDTH,
	                                   SCREEN_HEIGHT, 
	                                   SDL_WINDOW_SHOWN);
	if (win == nullptr)	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, 
	                                       SDL_RENDERER_ACCELERATED | 
	                                       SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	DrumSet *drumSet = new DrumSet(DRUMSET_X, DRUMSET_Y);
	StartButton *startBtn = new StartButton(START_BUTTON_X, BUTTONS_Y);
	StopButton *stopBtn = new StopButton(STOP_BUTTON_X, BUTTONS_Y);

	Context context(new IdleState(), drumSet, startBtn, stopBtn, ren);

	bool done = false;

	while (context.isActive()) {
		unsigned int frametime = SDL_GetTicks();

		context.update();

		if (SDL_GetTicks() - frametime < MINFRAMETIME)
			SDL_Delay(MINFRAMETIME - (SDL_GetTicks() - frametime));
	}

	delete drumSet;
	delete startBtn;
	delete stopBtn;

	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}