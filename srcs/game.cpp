#include "game.h"

State::~State () {}

void State::setContext (Context *context)
{
	curContext = context;
}

void State::action () {}

Context::Context (State *state,
                  DrumSet *drumSet, 
                  StartButton *startBtn, 
                  StopButton *stopBtn,
                  SDL_Renderer *ren) 
: mCurState(nullptr),
  mDrumSet(drumSet),
  mStartButton(startBtn),
  mStopButton(stopBtn),
  mRen(ren)
{
	changeState(state);
}

Context::~Context () {}

void Context::changeState (State *newState)
{
	if (mCurState != nullptr)
		delete mCurState;
	mCurState = newState;
	mCurState->setContext(this);
}

bool Context::isActive ()
{
	return active;
}

void Context::update ()
{
	mDrumSet->update();
	mStartButton->update();
	mStopButton->update();

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			active = false;
			break;
		} 
		if (event.type == SDL_MOUSEBUTTONDOWN) {
			mStartButton->tryPress(event.motion.x, event.motion.y);
			mStopButton->tryPress(event.motion.x, event.motion.y);
		} 
	}

	mCurState->action();
}

void Context::draw ()
{
	SDL_RenderClear(mRen);
	mDrumSet->draw(mRen);
	Textures::getInstance(mRen)->drawTexture(mRen, BACKGROUND, 0, 0);
	mStartButton->draw(mRen);
	mStopButton->draw(mRen);
	SDL_RenderPresent(mRen);
}

void Context::drawScore (std::string scoreStr)
{
	SDL_RenderClear(mRen);
	mDrumSet->draw(mRen);
	Textures::getInstance(mRen)->drawTexture(mRen, BACKGROUND, 0, 0);
	mStartButton->draw(mRen);
	mStopButton->draw(mRen);
	Textures::getInstance(mRen)->drawTexture(mRen, SCORE_FOREGROUND, 0, 0);
	TextRenderer::getInstance(mRen)->drawStr(mRen, scoreStr, 300, 220);
	SDL_RenderPresent(mRen);
}

IdleState::~IdleState () {}

void IdleState::action () 
{
	curContext->draw();

	if (curContext->mStartButton->isPressed()) {
		curContext->mDrumSet->startSpinning();
		curContext->changeState(new SpinningState());
	}
}

SpinningState::SpinningState () : mTimer(TIME_SPINNING) {}
SpinningState::~SpinningState () {}

void SpinningState::action () 
{
	curContext->draw();

	mTimer--;
	if (mTimer == 0 || curContext->mStopButton->isPressed()) {
		curContext->mDrumSet->stopSpinning();
		curContext->changeState(new StoppingState());
	}
}

StoppingState::~StoppingState () {}

void StoppingState::action ()  
{
	curContext->draw();

	if (curContext->mDrumSet->isStopped())
		curContext->changeState(new ScoreShowingState());
}

ScoreShowingState::~ScoreShowingState () {}

void ScoreShowingState::action () 
{
	int score = curContext->mDrumSet->getScore();
	std::string scoreStr;
	std::stringstream ss;
	ss << score;
	ss >> scoreStr;
	curContext->drawScore(scoreStr);

	if (curContext->event.type == SDL_MOUSEBUTTONDOWN)
		curContext->changeState(new IdleState());
}