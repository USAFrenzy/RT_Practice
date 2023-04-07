#include <RMRT/Camera/Camera.h>


rmrt::Camera::Camera() {
	auto aspectRatio{ 16.0 / 9.0 };
	auto viewportHeight{ 2.0 };
	auto viewportWidth{ aspectRatio * viewportHeight };
	auto focalLength{ 1.0 };

	m_origin = Point3(0, 0, 0);
	m_horizontal = Vec3(viewportWidth, 0.0, 0.0);
	m_vertical = Vec3(0.0, viewportHeight, 0.0);
	m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - Vec3(0, 0, focalLength);
}

rmrt::Camera::Camera(double aspectRatio, double viewPortHeight, double viewPortWidth, double focalLength)
	: m_origin(Point3(0, 0, 0)),
	m_horizontal(Vec3(viewPortWidth, 0.0, 0.0)),
	m_vertical(Vec3(0.0, viewPortHeight, 0.0)),
	m_lowerLeftCorner(m_origin - (m_horizontal / 2) - (m_vertical / 2) - Vec3(0, 0, focalLength))
{
}

rmrt::Camera::~Camera()
{
}

rmrt::Ray rmrt::Camera::GetRay(double u, double v) const
{
	return Ray(m_origin, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin);
}

void rmrt::Camera::SetFocalLength(double focalLength)
{
	m_lowerLeftCorner = (m_origin - (m_horizontal / 2) - (m_vertical / 2) - Vec3(0, 0, focalLength));
}
