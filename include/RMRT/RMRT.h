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
	constexpr double infinity{ std::numeric_limits<double>::infinity() };
	constexpr double pi{ 3.1415926535897932385 };
	constexpr auto rgb_factor{ 256 };

	// Our utility functions
	inline double DegToRad(double degrees) {
		return degrees * pi / 180.0;
	}

	inline double RandomDouble() {
		static std::uniform_real_distribution<double> distribution(0.0, 1.0);
		static std::mt19937 generator;
		return distribution(generator);
	}

	inline double RandomDouble(double min, double max) {
		static std::uniform_real_distribution<double> distribution(min, max);
		static std::mt19937 generator;
		return distribution(generator);
	}

	// Module 7.2 utility to update WriteColor()
	inline double Clamp(double x, double min, double max) {
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
		{ TempColor::white, rmrt::Color(1.0, 1.0, 1.0) },
		{TempColor::blue, rmrt::Color(0.5, 0.7, 1.0)},
		{TempColor::pink, rmrt::Color(0.7, 0.3, 0.3)},
		{TempColor::greenish, rmrt::Color(0.5, 0.63, 0.1)},
		{TempColor::bluish, rmrt::Color(0.1,0.1, 0.9)},
		{TempColor::goldish, rmrt::Color(0.9, 0.7, 0.3)},
		{TempColor::black, rmrt::Color(0,0,0)},
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
