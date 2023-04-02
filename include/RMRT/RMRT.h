#pragma once

#include <cmath>
#include <limits>
#include <memory>

// Our constants
constexpr double infinity{ std::numeric_limits<double>::infinity() };
constexpr double pi{ 3.1415926535897932385 };

// Our utility functions
inline double DegToRad(double degrees) {
	return degrees * pi / 180.0;
}

// Common headers to include
#include <RMRT/Ray.h>
#include <RMRT/Vec3.h>


#include <unordered_map> // temp usage for readabilitry in RayColor in Module 4.2
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