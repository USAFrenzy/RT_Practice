
#include <RMRT/Ray.h>

namespace rmrt {

	Ray::Ray(const point3& origin, const Vec3& direction) : m_origin(origin), m_direction(direction) {}

	point3 Ray::origin() const
	{
		return m_origin;
	}

	Vec3 Ray::direction() const
	{
		return m_direction;
	}

}