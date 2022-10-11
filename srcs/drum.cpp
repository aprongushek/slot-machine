#include "drum.h"

Drum::Drum () : mState(DRUMSTATE_MAINTAIN),
                mVelocity(0.0),
                mAcceleration(0.0),
                offs(0)
{
	mPrevChar = RNG::getInstance()->getNumber(0, CHARACTERS_AMOUNT-1);
	mCurChar = RNG::getInstance()->getNumber(0, CHARACTERS_AMOUNT-1);
	mNextChar = RNG::getInstance()->getNumber(0, CHARACTERS_AMOUNT-1);
}

void Drum::update ()
{
	switch (mState) {
		case DRUMSTATE_MAINTAIN:
			break;
		case DRUMSTATE_ACCELERATE:
			mVelocity += mAcceleration;
			if (mVelocity > MAX_VELOCITY) {
				mVelocity = MAX_VELOCITY;
				mState = DRUMSTATE_MAINTAIN;
			}
			break;
		case DRUMSTATE_DECELERATE:
			if (mVelocity > VELOCITY_THRESHOLD) {
				mVelocity -= mAcceleration;
			} else if (offs >= -2 && offs <= 2) {
				mVelocity = 0.0;
				mState = DRUMSTATE_MAINTAIN;
			}
			break;
	}

	offs += mVelocity;
	if (offs > CHARACTER_HEIGHT / 2) {
		offs -= CHARACTER_HEIGHT;
		mPrevChar = mCurChar;
		mCurChar = mNextChar;
		mNextChar = RNG::getInstance()->getNumber(0, CHARACTERS_AMOUNT-1);
	}
}

float Drum::getVelocity ()
{
	return mVelocity;
}

int Drum::getCurrentChar ()
{
	return mCurChar;
}

void Drum::startSpinning ()
{
	mAcceleration = RNG::getInstance()->getNumber(MIN_ACCELERATION*EXPONENT,
	                                              MAX_ACCELERATION*EXPONENT);
	mAcceleration /= EXPONENT;
	mState = DRUMSTATE_ACCELERATE;
}

void Drum::stopSpinning ()
{
	mAcceleration = RNG::getInstance()->getNumber(MIN_ACCELERATION*EXPONENT,
	                                              MAX_ACCELERATION*EXPONENT);
	mAcceleration /= EXPONENT;
	mState = DRUMSTATE_DECELERATE;
}

void Drum::draw (SDL_Renderer *ren, int x, int y)
{
	Textures::getInstance(ren)->drawTexture(ren, (TextureID)(CHARACTER_0+mCurChar),
	                                        x, y+offs);
	Textures::getInstance(ren)->drawTexture(ren, (TextureID)(CHARACTER_0+mNextChar),
	                                        x, y+offs-CHARACTER_HEIGHT);
	Textures::getInstance(ren)->drawTexture(ren, (TextureID)(CHARACTER_0+mPrevChar),
		                                    x, y+offs+CHARACTER_HEIGHT);
}

DrumSet::DrumSet (int x, int y) : mX(x), mY(y) {}

void DrumSet::update ()
{
	for (int i = 0; i < DRUMS_AMOUNT; i++)
		mDrums[i].update();
}

void DrumSet::startSpinning ()
{
	for (int i = 0; i < DRUMS_AMOUNT; i++)
		mDrums[i].startSpinning();
}

void DrumSet::stopSpinning ()
{
	for (int i = 0; i < DRUMS_AMOUNT; i++)
		mDrums[i].stopSpinning();
}

bool DrumSet::isStopped ()
{
	bool result = true;
	for (int i = 0; i < DRUMS_AMOUNT; i++)
		if (mDrums[i].getVelocity() != 0.0) {
			result = false;
			break;
		}
	return result;
}

void DrumSet::draw (SDL_Renderer *ren)
{
	for (int i = 0; i < DRUMS_AMOUNT; i++)
		mDrums[i].draw(ren, mX + CHARACTER_WIDTH * i, mY);
}

int DrumSet::getScore ()
{
	int matches[CHARACTERS_AMOUNT];
	for (int i = 0; i < CHARACTERS_AMOUNT; i++)
		matches[i] = 0;

	for (int i = 0; i < DRUMS_AMOUNT; i++)
		matches[mDrums[i].getCurrentChar()]++;

	int max = 0;
	for (int i = 0; i < CHARACTERS_AMOUNT; i++)
		if (matches[i] > max)
			max = matches[i];

	return max;
}
