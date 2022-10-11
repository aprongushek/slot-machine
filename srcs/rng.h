#ifndef RNG_H
#define RNG_H

#include <cstdlib>
#include <ctime>

// simpliest random number generator
class RNG {
private:
	static RNG *instance;

	RNG ();

public:
	static RNG *getInstance ();

	unsigned int getNumber (unsigned int min, unsigned int max);
};

#endif