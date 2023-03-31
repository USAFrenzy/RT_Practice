#pragma once

#include <RMRT/Vec3.h>

namespace rmrt {

	class Ray {
	public:
		Ray() {}
		Ray(const point3& origin, const Vec3& direction);

		point3 Origin() const;
		Vec3 Direction () const;
		color RayColor(const Ray& ray);

	private:
		point3 m_origin;
		Vec3 m_direction;
	};
}