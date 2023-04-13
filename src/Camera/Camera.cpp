#include <RMRT/Camera/Camera.h>


rmrt::Camera::Camera(const Point3& lookFrom, const Point3& lookAt, const Vec3& vertUp, float vertFOV, float aspectRatio) {

	auto theta {DegToRad(vertFOV)};
	auto h {tan(theta/2)};
	auto viewportHeight {2.0f *h};
	auto viewportWidth {aspectRatio*viewportHeight};

	auto w {UnitVector(lookFrom - lookAt)};
	auto u {UnitVector(Cross(vertUp, w))};
	auto v {Cross(w, u)};

	m_origin = lookFrom;
	m_horizontal = viewportWidth*u;
	m_vertical = viewportHeight*v;
	m_lowerLeftCorner = m_origin - m_horizontal/2 - m_vertical/2 - w;
}

rmrt::Camera::~Camera()
{
}

rmrt::Ray rmrt::Camera::GetRay(float u, float v) const
{
	return Ray(m_origin, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin);
}

void rmrt::Camera::SetFocalLength(const Point3& origin, const Point3& target)
{
	m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - UnitVector(origin - target);
}
