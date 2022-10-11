#ifndef TEXTURES_H
#define TEXTURES_H

#include <string>

#include "SDL2/SDL.h"

#define TEXTURES_AMOUNT 9
enum TextureID {
	BACKGROUND = 0,
	SCORE_FOREGROUND,
	START_BUTTON_RELEASED,
	START_BUTTON_PRESSED,
	STOP_BUTTON_RELEASED,
	STOP_BUTTON_PRESSED,
	CHARACTER_0,
	CHARACTER_1,
	CHARACTER_2
};

struct Size {
	int w;
	int h;
};

// sort of a container for the (almost) all textures in game
class Textures {
private:
	static Textures *instance;

	std::string texturePaths[TEXTURES_AMOUNT];
	Size sizes[TEXTURES_AMOUNT];
	SDL_Texture *textures[TEXTURES_AMOUNT];
	
	void loadAllTextures (SDL_Renderer *ren);

	Textures (SDL_Renderer *ren);
	~Textures ();

public:
	static Textures *getInstance (SDL_Renderer *ren);

	void drawTexture (SDL_Renderer *ren, TextureID id, int x, int y);
};

#endif