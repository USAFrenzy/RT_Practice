
#include <RMRT/Ray.h>


#include <unordered_map> // temp usage for readabilitry in RayColor in Module 4.2


namespace rmrt {

	Ray::Ray(const Point3& origin, const Vec3& direction) : m_origin(origin), m_direction(direction) {}

	Point3 Ray::Origin() const
	{
		return m_origin;
	}

	Vec3 Ray::Direction() const
	{
		return m_direction;
	}

	Point3 Ray::At(double t) const
	{
		return m_origin + (t * m_direction);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Temp usage for readability for module 4.2's RayColor() function
	enum class TempColor {
		white,
		blue,
	};
	static  std::unordered_map<TempColor, Color>  colorMap =
	{
		{ TempColor::white, Color(1.0, 1.0, 1.0) },
		{TempColor::blue, Color(0.5, 0.7, 1.0)},
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// This function is used to blend the colors in the background, the author states it's a gradient of blue to white.
	// This is using linear interpolation with the equation: 
	// 
	//                      blendedValue = (1-t)*startValue + (t*endValue)
	// 
	//  NOTE: In the paragraph under this exceprt in module 4.2, the explanation basically tells us that this is dependant on
	//    clamping the Color points between '0' and '1' for the gradient. (when t = 0.0 -> white, when t = 1.0 -> blue) on the 
	//    normalized Y-Axis.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Color Ray::RayColor(const Ray& ray)
	{
		// From module 5.2, we are hard-coding the sphere center, radius, and color produced when the ray hits the sphere;
		// In actual code, this would most likely be dynamic in the form of input paramaters and attributes instead.
		// Module 6 added a condition on shading the sphere if the ray hits it by normalizing the vector point |_ to the sphere.
		if (auto t{ SphereHit(Point3(0, 0, -1), 0.5, ray) };  t > 0.0) {
			Vec3 n{ UnitVector(ray.At(t) - Vec3(0,0,-1)) };
			return 0.5 * Color(n.X() + 1, n.Y() + 1, n.Z() + 1);
		}
		else {
			Vec3 unitDirection{ UnitVector(ray.Direction()) };
			t = 0.5 * (unitDirection.Y() + 1.0);
			return ((1.0 - t) * colorMap[TempColor::white]) + (t * colorMap[TempColor::blue]);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// The 'SphereHit()' function is working off the general formula "x^2 + y^2 + z^2 = R^2" for a sphere.
	// 
	// If the sphere isn't located at the origin, the equation becomes "(x-Cx)^2 +(y-Cy)^2 +(z-Cz)^2 = R^2", 
	// where Cx, Cy, and Cz are the coordinates of the sphere and x, y, and z are the ray coordinates.
	//
	// If the lefthand side is > R^2, then the point exists outside of the sphere.
	// If the lefthand side is < R^2, then the point exists inside the sphere.
	// If the lefthand side == R^2, then the point hits the sphere.
	//
	// The author simplifies this (and I like this simplification because it avoids a super messy expansion) to:
	// (P - C) * (P - C) = r^2, where 'P' is the point coordinates, and 'C' is the sphere coordinates
	//
	// Given the equation of a ray is a simple slope formula of  'y =mx + b', we substitute this formula in terms of 'b', or as 
	// the author has in his formula, in terms of 't' (P(t) = A + tb). This finds the point that the ray intersects the sphere.
	//
	// 1) Therefore, the above equation becomes: "(P(t) - C) * (P(t) - C) = r^2" 
	// 2) When we substitute the full equation of the ray in, we get: "(A + tb - C) * (A + tb - C) = r^2"
	// 3) Simplifying the equation, this becomes: "(t^2b * b) + (2tb*(A - C))+ ((A - C)*(A - C)) - r^2 = 0"
	//     where the '*' are vector dot products, not strictly multiplication symbols both here and in point '2'.
	// 4) Given that most of the variables are known, besides 't', this becomes a quadratic in terms of  't'
	// 5a) If the discriminant is > 0, there are two solutions, meaning two intersections
	// 5b) If the discriminant is < 0, there are no solutions, meaning no intersections
	// 5c) If the discriminant == 0, there is exactly one solution, meaning there is exactly one intersection, the tangent.   
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	double Ray::SphereHit(const Point3& center, double radius, const Ray& ray)
	{
		Vec3 originCenter{ ray.Origin() - center };
		// Both 'a' and 'c' were simplified in module 6.2 due to the vector attribute that states: 
		// A vector dot with itself  == length^2 of that vector
		// 'b' was simplified due to '2' cancelling out ==> discriminant and return check was simplified as well
		auto a{ ray.Direction().LengthSquared() };
		auto bHalf{ Dot(originCenter, ray.Direction()) };
		auto c{ originCenter.LengthSquared() - (radius * radius) };
		auto discriminant{ bHalf * bHalf - (a * c) };
		// My note from last commit was addressed in module 6 based on normalizing the vectors for shading
		return discriminant < 0 ? -1.0 : ((-bHalf - std::sqrt(discriminant)) / a);
	}

}