#include "rng.h"

RNG *RNG::instance = nullptr;

RNG::RNG ()
{
	srand(time(nullptr));
}

RNG *RNG::getInstance ()
{
	if (instance == nullptr)
		instance = new RNG();
	return instance;
}

unsigned int RNG::getNumber (unsigned int min, unsigned int max)
{
	return (rand() % (max - min + 1)) + min;
}