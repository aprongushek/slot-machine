#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SDL2/SDL.h"

#include "textures.h"

// simple class that adds ability to render text on screen (only numbers for now) 
class TextRenderer {
private:
	SDL_Texture *alphabet;
	Size size;

	static TextRenderer *instance;

	TextRenderer (SDL_Renderer *ren);
	~TextRenderer ();

public:
	static TextRenderer *getInstance(SDL_Renderer *ren);

	void drawStr (SDL_Renderer *ren, std::string str, int x, int y);
};

#endif