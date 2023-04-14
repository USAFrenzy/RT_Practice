#pragma once

#include <RMRT/RMRT.h>

namespace rmrt {

	class Camera
	{
	public:
		Camera(const Point3& lookFrom, const Point3& lookAt, const Vec3& vertUp, float vertFOV, float aspectRatio, float aperture, float focusDistance);
		~Camera();

		Ray GetRay(float u, float v) const;
		void SetFocalLength(const Point3& origin, const Point3& targett);
		void SetDepthOfField(float focalDistance);

	private:
		Point3 m_origin;
		Point3 m_lowerLeftCorner;
		Vec3 m_horizontal;
		Vec3 m_vertical;
		Vec3 m_camVertPos;
		Vec3 m_u;
		Vec3 m_v;
		Vec3 m_w;
		float m_lensRadius;
		float m_focalDistance;
		float m_viewWidth;
		float m_viewHeight;
	};

}