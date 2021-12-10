#ifndef RANDOMNUMBERGENERATOR_H
#define RANDOMNUMBERGENERATOR_H
#include <random>

class RandomIntGenerator
{
private:
    std::mt19937 rng;
    std::uniform_int_distribution<int> distribution;
public:
    RandomIntGenerator(int min, int max);
    int getRandomInt();
};


#endif // RANDOMIntGENERATOR_H
