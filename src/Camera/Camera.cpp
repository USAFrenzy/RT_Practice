#include <RMRT/Camera/Camera.h>


rmrt::Camera::Camera(const Point3& lookFrom, const Point3& lookAt, const Vec3& vertUp, float vertFOV, float aspectRatio, float aperture, float focusDistance) {

	auto theta {DegToRad(vertFOV)};
	auto h {tan(theta/2)};
	m_camVertPos = vertUp;
	m_viewHeight = 2.0f *h;
	m_viewWidth = aspectRatio*m_viewHeight;

	m_w = UnitVector(lookFrom - lookAt);
	m_u = UnitVector(Cross(vertUp, m_w));
	m_v = Cross(m_w, m_u);

	m_origin = lookFrom;
	m_horizontal = focusDistance*m_viewWidth*m_u;
	m_vertical = focusDistance*m_viewHeight*m_v;
	m_focalDistance = focusDistance;
	m_lowerLeftCorner = m_origin - m_horizontal/2 - m_vertical/2 - (m_focalDistance*m_w);

	m_lensRadius = aperture/2;
}

rmrt::Camera::~Camera()
{
}

rmrt::Ray rmrt::Camera::GetRay(float u, float v) const
{
	Vec3 rd {m_lensRadius*RandomInUnitDisc()};
	Vec3 offset {m_u*rd.X() + m_v*rd.Y()};
	return Ray(m_origin+offset, m_lowerLeftCorner + (u * m_horizontal) + (v * m_vertical) - m_origin - offset);
}

void rmrt::Camera::SetDepthOfField(float focalDistance)
{
	m_focalDistance = focalDistance;

}

void rmrt::Camera::SetFocalLength(const Point3& origin, const Point3& target)
{
	m_w = UnitVector(origin-target);
	m_u = UnitVector(Cross(m_camVertPos, m_w));
	m_v = Cross(m_w, m_u);
	m_origin = origin;
	m_horizontal = m_focalDistance* m_viewWidth * m_u;
	m_vertical = m_focalDistance * m_viewHeight * m_v;
	m_lowerLeftCorner = m_origin - (m_horizontal / 2) - (m_vertical / 2) - (m_focalDistance * m_w);
}
