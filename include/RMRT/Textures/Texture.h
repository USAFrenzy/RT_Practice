#pragma once

#include <RMRT/Vec3.h>

namespace rmrt {

	class Texture
	{
	  public:
		constexpr virtual Color Value(float u, float v, const Point3& p) const = 0;
	};

	class SolidColor: public Texture
	{
	  public:
		constexpr SolidColor() { }
		constexpr SolidColor(Color color): m_colorValue(color) { }
		constexpr SolidColor(float red, float green, float blue): m_colorValue(Color(red, green, blue)) { }
		constexpr virtual Color Value(float u, float v, const Point3& p) const override {
			return m_colorValue;
		}

	  private:
		Color m_colorValue;
	};
}    // namespace rmrt