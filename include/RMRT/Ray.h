#pragma once

#include <RMRT/Vec3.h>

namespace rmrt {

	class Ray
	{
	  public:
		inline constexpr Ray() { }
		inline constexpr Ray(const Point3& origin, const Vec3& direction, float time = 0.0): m_origin(origin), m_direction(direction), m_time(time) { }

		inline constexpr const Point3& Origin() const {
			return m_origin;
		}
		inline constexpr const Vec3& Direction() const {
			return m_direction;
		}
		inline constexpr Point3 At(float t) const {
			return m_origin + (t * m_direction);
		}
		inline constexpr float Time() const {
			return m_time;
		}

	  private:
		Point3 m_origin;
		Vec3 m_direction;
		float m_time;
	};
}    // namespace rmrt