#ifndef PERLINNOISE_H_
#define PERLINNOISE_H_

#include <cmath>
#include <random>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iostream>

class PerlinNoise {

public:
	PerlinNoise();
	std::vector<int> getCoordinates(const int width, const int length, const int seed, const int octaves, const float bias);
};

#endif
