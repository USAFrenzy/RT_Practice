
#include <RMRT/Ray.h>


#include <unordered_map> // temp usage for readabilitry in RayColor in Module 4.2


namespace rmrt {

	Ray::Ray(const point3& origin, const Vec3& direction) : m_origin(origin), m_direction(direction) {}

	point3 Ray::Origin() const
	{
		return m_origin;
	}

	Vec3 Ray::Direction() const
	{
		return m_direction;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Temp usage for readability for module 4.2's RayColor() function
	enum class TempColor {
		white,
		blue,
	};
	static  std::unordered_map<TempColor, color>  colorMap =
	{
		{ TempColor::white, color(1.0, 1.0, 1.0) },
		{TempColor::blue, color(0.5, 0.7, 1.0)},
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// This function is used to blend the colors in the background, the author states it's a gradient of blue to white.
	// This is using linear interpolation with the equation: 
	// 
	//                      blendedValue = (1-t)*startValue + (t*endValue)
	// 
	//  NOTE: In the paragraph under this exceprt in module 4.2, the explanation basically tells us that this is dependant on
	//    clamping the color points between '0' and '1' for the gradient. (when t = 0.0 -> white, when t = 1.0 -> blue) on the 
	//    normalized Y-Axis.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	color Ray::RayColor(const Ray& ray)
	{
		Vec3 unitDirection{ UnitVector(ray.Direction()) };
		auto t{ 0.5 * (unitDirection.Y() + 1.0) };
		return ((1.0 - t) * colorMap[TempColor::white]) + (t * colorMap[TempColor::blue]);
	}

}