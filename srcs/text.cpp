#include "text.h"

TextRenderer *TextRenderer::instance = nullptr;

TextRenderer::TextRenderer (SDL_Renderer *ren)
{
	SDL_Surface *bmp = SDL_LoadBMP("resources\\digits.bmp");
	size.w = bmp->w / 10;
	size.h = bmp->h;
	alphabet = SDL_CreateTextureFromSurface(ren, bmp);
	SDL_FreeSurface(bmp);
}

TextRenderer::~TextRenderer ()
{
	SDL_DestroyTexture(alphabet);
}

TextRenderer *TextRenderer::getInstance(SDL_Renderer *ren)
{
	if (instance == nullptr)
		instance = new TextRenderer(ren);
	return instance;
}

void TextRenderer::drawStr (SDL_Renderer *ren, std::string str, int x, int y)
{
	for (int i = 0; i < str.length(); i++) {
		SDL_Rect rectDst;
		rectDst.x = x + size.w * i;
		rectDst.y = y;
		rectDst.w = size.w;
		rectDst.h = size.h;
	
		int offs = str[i] - '0';

		SDL_Rect rectSrc;
		rectSrc.x = offs * size.w;
		rectSrc.y = 0;
		rectSrc.w = size.w;
		rectSrc.h = size.h;	
	
		SDL_RenderCopy(ren, alphabet, &rectSrc, &rectDst);
	}
}