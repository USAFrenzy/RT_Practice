#include <RMRT/Camera/Camera.h>


rmrt::Camera::Camera() {
	auto aspectRatio{ 16.0f / 9.0f };
	auto viewportHeight{ 2.0f };
	auto viewportWidth{ aspectRatio * viewportHeight };
	auto focalLength{ 1.0f };

	m_origin = Point3(0.0f, 0.0f, 0.0f);
	m_horizontal = Vec3(viewportWidth, 0.0f, 0.0f);
	m_vertical = Vec3(0.0f, viewportHeight, 0.0f);
	m_lowerLeftCorner = m_origin - (m_horizontal / 2.0f) - (m_vertical / 2.0f) - Vec3(0.0f, 0.0f, focalLength);
}

rmrt::Camera::Camera(float aspectRatio, float viewPortHeight, float viewPortWidth, float focalLength)
	: m_origin(Point3(0.0f, 0.0f, 0.0f)),
	m_horizontal(Vec3(viewPortWidth, 0.0f, 0.0f)),
	m_vertical(Vec3(0.0f, viewPortHeight, 0.0f)),
	m_lowerLeftCorner(m_origin - (m_horizontal / 2.0f) - (m_vertical / 2.0f) - Vec3(0.0f, 0.0f, focalLength))
{
}

rmrt::Camera::~Camera()
{
}

rmrt::Ray rmrt::Camera::GetRay(float u, float v) const
{
	return Ray(m_origin, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin);
}

void rmrt::Camera::SetFocalLength(float focalLength)
{
	m_lowerLeftCorner = (m_origin - (m_horizontal / 2.0f) - (m_vertical / 2.0f) - Vec3(0.0f, 0.0f, focalLength));
}
