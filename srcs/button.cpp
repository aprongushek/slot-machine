#include "button.h"

Button::Button (int x, int y) : mX(x), 
                                mY(y), 
                                mTimer(0), 
                                mState(BUTTON_RELEASED) 
{}

Button::~Button () {}

void Button::update ()
{
	if (mState == BUTTON_PRESSED) {
		mTimer--;
		if (mTimer == 0)
			mState = BUTTON_RELEASED;
	}
}

void Button::tryPress (int x, int y)
{
	if ((x >= mX && x <= mX + BUTTON_WIDTH) &&
	    (y >= mY && y <= mY + BUTTON_HEIGHT)) {
		mTimer = TIME_PRESSED;
		mState = BUTTON_PRESSED;
	}
}

bool Button::isPressed ()
{
	return mState;
}

void Button::draw (SDL_Renderer *ren) {}

StartButton::StartButton (int x, int y) : Button(x, y) {}
StartButton::~StartButton () {}

void StartButton::draw (SDL_Renderer *ren) 
{
	if (mState == BUTTON_PRESSED)
		Textures::getInstance(ren)->drawTexture(ren, START_BUTTON_PRESSED, 
		                                        mX, mY);
	else
		Textures::getInstance(ren)->drawTexture(ren, START_BUTTON_RELEASED,
		                                        mX, mY);
}

StopButton::StopButton (int x, int y) : Button(x, y) {}
StopButton::~StopButton () {}

void StopButton::draw (SDL_Renderer *ren) 
{
	if (mState == BUTTON_PRESSED)
		Textures::getInstance(ren)->drawTexture(ren, STOP_BUTTON_PRESSED, 
		                                        mX, mY);
	else
		Textures::getInstance(ren)->drawTexture(ren, STOP_BUTTON_RELEASED,
		                                        mX, mY);
}