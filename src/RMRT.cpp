#include <RMRT/RMRT.h>

// #include <random> // Module 7.1 Random Number Generator Utility

namespace rmrt {

	float DegToRad(float degrees) {
		return static_cast<float>(degrees * pi / 180.0f);
	}

	float RandomDouble() {
		//static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		//static std::mt19937 generator;
		//return distribution(generator);
		return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) + 1.0f);
	}

	float RandomDouble(float min, float max) {
		//static std::uniform_real_distribution<float> distribution(min, max);
		//static std::mt19937 generator;
		//return distribution(generator);
		return min + (max - min) * RandomDouble();
	}

	int RandomInt(int min, int max)
	{
		return static_cast<int>(RandomDouble(static_cast<float>(min), static_cast<float>(max+1)));
	}

}
