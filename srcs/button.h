#ifndef BUTTON_H
#define BUTTON_H

#include <ctime>
#include "SDL2/SDL.h"
#include "textures.h"

#define BUTTON_PRESSED true
#define BUTTON_RELEASED false

#define BUTTON_WIDTH 130
#define BUTTON_HEIGHT 60

#define TIME_PRESSED 10

// buttons parent class
class Button {
protected:
	bool mState;
	unsigned int mTimer;

	int mX;
	int mY;

public:
	Button (int x, int y);
	virtual ~Button ();

	void update ();

	void tryPress (int x, int y);

	bool isPressed ();

	virtual void draw (SDL_Renderer *ren);
};

class StartButton : public Button {
public:
	StartButton (int x, int y);
	~StartButton () override;

	void draw (SDL_Renderer *ren) override;
};

class StopButton : public Button {
public:
	StopButton (int x, int y);
	~StopButton () override;

	void draw (SDL_Renderer *ren) override;
};

#endif