#pragma once

#include <RMRT/Vec3.h>

namespace rmrt {

	class Ray {
	public:
		Ray() {}
		Ray(const Point3& origin, const Vec3& direction);

		Point3 Origin() const;
		Vec3 Direction () const;
		Point3 At(double t) const;
		Color RayColor(const Ray& ray);
		double SphereHit(const Point3& center, double radius, const Ray& r);
			
	private:
		Point3 m_origin;
		Vec3 m_direction;
	};
}