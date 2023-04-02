#pragma once

#include <cmath>
#include <limits>
#include <memory>
#include <random> // Module 7.1 Random Number Generator Utility
#include <unordered_map> // temp usage for readabilitry in RayColor in Module 4.2

// Common headers to include
#include <RMRT/Ray.h>
#include <RMRT/Vec3.h>


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

	// Module 7.2 utility to update WriteColor()
	inline double Clamp(double x, double min, double max) {
		if (x < min) return min;
		if (x > max) return max;
		return x;
	}

	inline void WriteColor(std::ostream& out, rmrt::Color pixelColor, int samplesPerPixel)
	{
		auto scale{ 1.0 / samplesPerPixel };
		auto r{ pixelColor.X() * scale };
		auto g{ pixelColor.Y() * scale };
		auto b{ pixelColor.Z() * scale };
		// This basically does what the initial code in the 2.1 module of 'Raytracing In One Weekend' accomplished, 
		// except it now uses the ostream class to write to the console (This is from module 3.3)
		//
		// The addition of the above lines with the scale and the function Clamp() is found from module 7.2
		out << static_cast<int>(rgb_factor * rmrt::Clamp(r, 0.0, 0.999)) << ' '
			<< static_cast<int>(rgb_factor * rmrt::Clamp(g, 0.0, 0.999)) << ' '
			<< static_cast<int>(rgb_factor * rmrt::Clamp(b, 0.0, 0.999)) << '\n';
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Temp usage for readability for module 4.2's RayColor() function
	enum class TempColor {
		white,
		blue,
	};
	static  std::unordered_map<TempColor, rmrt::Color>  colorMap =
	{
		{ TempColor::white, rmrt::Color(1.0, 1.0, 1.0) },
		{TempColor::blue, rmrt::Color(0.5, 0.7, 1.0)},
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
