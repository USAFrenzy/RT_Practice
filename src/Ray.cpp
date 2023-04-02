
#include <RMRT/Ray.h>

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