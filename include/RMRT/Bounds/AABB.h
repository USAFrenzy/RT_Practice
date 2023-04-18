#pragma once

#include <RMRT/Ray.h>

namespace rmrt {

	class AABB
	{
	  public:
		inline constexpr AABB() { }
		inline constexpr AABB(const Point3& a, const Point3& b): m_min(a), m_max(b) { }

		inline constexpr Point3 Max() const {
			return m_max;
		}
		inline constexpr Point3 Min() const {
			return m_min;
		}

		inline constexpr bool Hit(const Ray& ray, float tMin, float tMax) const {
			const auto& rayOrigin { ray.Origin() };
			const auto& rayDirection { ray.Direction() };
			auto a { 0 };
			for( ;; ) {
					auto invD { 1.0f / rayDirection[ a ] };
					auto t0 { (m_min[ a ] - rayOrigin[ a ]) * invD };
					auto t1 { (m_max[ a ] - rayOrigin[ a ]) * invD };
					if( invD < 0.0f ) std::swap(t0, t1);
					tMin = t0 > tMin ? t0 : tMin;
					tMax = t1 < tMax ? t1 : tMax;
					if( tMax <= tMin ) return false;
					if( ++a < 3 ) continue;
					return true;
				}
		}

	  private:
		Point3 m_min;
		Point3 m_max;
	};
	AABB SurroundingBox(AABB box0, AABB box1);
}    // namespace rmrt
