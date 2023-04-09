#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random> // Module 7.1 Random Number Generator Utility
#include <unordered_map> // temp usage for readabilitry in RayColor in Module 4.2

// Common headers to include
#include <RMRT/Ray.h>

namespace rmrt {

	// Our constants
	constexpr float infinity{ std::numeric_limits<float>::infinity() };
	constexpr float pi{ 3.1415926535897932385f };
	constexpr float rgb_factor{ 256.0f };

	// Our utility functions
	inline float DegToRad(float degrees) {
		return static_cast<float>(degrees * pi / 180.0f);
	}

	inline float RandomDouble() {
		static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
		static  std::mt19937 generator;
		return distribution(generator);
	}

	inline float RandomDouble(float min, float max) {
		static std::uniform_real_distribution<float> distribution(min, max);
		static std::mt19937 generator;
		return distribution(generator);
	}

	// Module 7.2 utility to update WriteColor()
	inline float Clamp(float x, float min, float max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}



	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Temp usage for readability for module 4.2's RayColor() function
	enum class TempColor {
		white,
		blue,
		bluish,
		pink,
		goldish,
		greenish,
		black,
	};
	static  std::unordered_map<TempColor, rmrt::Color>  colorMap =
	{
		{ TempColor::white, rmrt::Color(1.0f, 1.0f, 1.0f) },
		{TempColor::blue, rmrt::Color(0.5f, 0.7f, 1.0f)},
		{TempColor::pink, rmrt::Color(0.7f, 0.3f, 0.3f)},
		{TempColor::greenish, rmrt::Color(0.5f, 0.63f, 0.1f)},
		{TempColor::bluish, rmrt::Color(0.1f,0.1f, 0.9f)},
		{TempColor::goldish, rmrt::Color(0.9f, 0.7f, 0.3f)},
		{TempColor::black, rmrt::Color(0.0f, 0.0f, 0.0f)},
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
