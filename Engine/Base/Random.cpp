#include "Random.h"
#include <cstdlib>

double ArtemisEngine::Random::Range(double min, double max)
{
    return Value() * (max - min) + min;
}

double ArtemisEngine::Random::Value()
{
    return (double(rand()) / RAND_MAX);
}
