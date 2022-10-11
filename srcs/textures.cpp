#include "textures.h"

Textures *Textures::instance = nullptr;

void Textures::loadAllTextures (SDL_Renderer *ren)
{
	for (int i = 0; i < TEXTURES_AMOUNT; i++) {
		SDL_Surface *bmp = SDL_LoadBMP(texturePaths[i].c_str());
		sizes[i].w = bmp->w;
		sizes[i].h = bmp->h;
		textures[i] = SDL_CreateTextureFromSurface(ren, bmp);
		SDL_FreeSurface(bmp);
	}
}

Textures::Textures (SDL_Renderer *ren)
{
	texturePaths[BACKGROUND] = "resources\\background.bmp";
	texturePaths[SCORE_FOREGROUND] = "resources\\score_foreground.bmp";
	texturePaths[START_BUTTON_RELEASED] = "resources\\start_button_released.bmp";
	texturePaths[START_BUTTON_PRESSED] = "resources\\start_button_pressed.bmp";
	texturePaths[STOP_BUTTON_RELEASED] = "resources\\stop_button_released.bmp";
	texturePaths[STOP_BUTTON_PRESSED] = "resources\\stop_button_pressed.bmp";
	texturePaths[CHARACTER_0] = "resources\\character_0.bmp";
	texturePaths[CHARACTER_1] = "resources\\character_1.bmp";
	texturePaths[CHARACTER_2] = "resources\\character_2.bmp";

	loadAllTextures(ren);
}

Textures::~Textures ()
{
	for (int i = 0; i < TEXTURES_AMOUNT; i++)
		SDL_DestroyTexture(textures[i]);
}

Textures *Textures::getInstance (SDL_Renderer *ren)
{
	if (instance == nullptr)
		instance = new Textures(ren);
	return instance;
}

void Textures::drawTexture(SDL_Renderer *ren, TextureID id, int x, int y)
{
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = sizes[id].w;
	rect.h = sizes[id].h;

	SDL_RenderCopy(ren, textures[id], nullptr, &rect);
}