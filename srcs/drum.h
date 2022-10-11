#ifndef DRUM_H
#define DRUM_H

#include "SDL2/SDL.h"

#include "rng.h"
#include "textures.h"

#define CHARACTERS_AMOUNT 3
#define CHARACTER_HEIGHT 119
#define CHARACTER_WIDTH 92

#define MAX_VELOCITY 40
#define VELOCITY_THRESHOLD 3 
#define MAX_OFFSET 60

#define MIN_ACCELERATION 0.2
#define MAX_ACCELERATION 1.0
#define EXPONENT 10

#define DRUMS_AMOUNT 5

enum DrumStates {
	DRUMSTATE_MAINTAIN = 0,
	DRUMSTATE_ACCELERATE,
	DRUMSTATE_DECELERATE
};

// class of the individual drum
class Drum {
private:
	int mPrevChar;
	int mCurChar;
	int mNextChar;

	DrumStates mState;
	float mVelocity;
	float mAcceleration;

	int offs;

public:
	Drum ();

	void update ();

	float getVelocity ();
	int getCurrentChar ();

	void startSpinning ();
	void stopSpinning ();

	void draw (SDL_Renderer *ren, int x, int y);
};

class DrumSet {
private:
	Drum mDrums[DRUMS_AMOUNT];

	int mX;
	int mY;

public:
	DrumSet (int x, int y);

	void update ();

	void startSpinning ();
	void stopSpinning ();

	bool isStopped ();

	void draw (SDL_Renderer *ren);

	int getScore ();
};

#endif