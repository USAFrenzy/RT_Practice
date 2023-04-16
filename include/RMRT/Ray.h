#pragma once

#include <RMRT/Vec3.h>

namespace rmrt {

	class Ray {
	public:
		inline constexpr Ray() {}
		inline constexpr Ray(const Point3& origin, const Vec3& direction) : m_origin(origin), m_direction(direction) {}

		inline constexpr const Point3& Origin() const
		{
			return m_origin;
		}

		inline constexpr const Vec3& Direction () const
		{
			return m_direction;
		}

		inline constexpr Point3 At(float t) const
		{
			return m_origin + (t * m_direction);
		}
			
	private:
		Point3 m_origin;
		Vec3 m_direction;
	};
}