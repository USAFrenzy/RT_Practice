#pragma once

#include <RMRT/Vec3.h>

namespace rmrt {

	class Ray {
	public:
		Ray() {}
		Ray(const Point3& origin, const Vec3& direction);

		Point3 Origin() const;
		Vec3 Direction () const;
		Color RayColor(const Ray& ray);
		bool SphereHit(const Point3& center, double radius, const Ray& r);
			
	private:
		Point3 m_origin;
		Vec3 m_direction;
	};
}