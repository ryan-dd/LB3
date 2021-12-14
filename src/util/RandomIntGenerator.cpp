#include "RandomIntGenerator.h"

namespace LB3
{
RandomIntGenerator::RandomIntGenerator(int min, int max):
    rng(std::random_device{}()),
    distribution(min, max)
{
}

int RandomIntGenerator::getRandomInt()
{   
    return distribution(rng);
}
}
