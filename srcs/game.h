#ifndef GAME_H
#define GAME_H

#include <string>
#include <sstream>

#include "SDL2/SDL.h"

#include "textures.h"
#include "drum.h"
#include "button.h"
#include "text.h"

#define TIME_SPINNING 500

class Context;

// parent class for states of the machine 
class State {
protected:
	Context *curContext;

public:
	virtual ~State ();

	void setContext (Context *context);

	virtual void action ();
};

// finite-state machine implementation
class Context {
	friend class State;
	friend class IdleState;
	friend class SpinningState;
	friend class StoppingState;
	friend class ScoreShowingState;

private:
	State *mCurState;

	DrumSet *mDrumSet;
	StartButton *mStartButton;
	StopButton *mStopButton;

	SDL_Renderer *mRen;

	SDL_Event event;

	bool active;

public:
	Context (State *state,
	         DrumSet *drumSet, 
             StartButton *startBtn, 
             StopButton *stopBtn,
	         SDL_Renderer *ren);
	~Context ();

	void changeState (State *newState);

	bool isActive ();

	void update ();

	void draw ();
	void drawScore (std::string scoreStr);
};

// concrete states of the machine
class IdleState : public State {
public:
	~IdleState () override;

	void action () override;
};

class SpinningState : public State {
private:
	int mTimer;
public:
	SpinningState ();
	~SpinningState () override;

	void action () override;
};

class StoppingState : public State {
public:
	~StoppingState () override;

	void action () override;
};

class ScoreShowingState : public State {
public:
	~ScoreShowingState () override;

	void action () override;
};

#endif