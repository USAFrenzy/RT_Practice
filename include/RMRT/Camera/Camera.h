#pragma once

#include <RMRT/RMRT.h>

namespace rmrt {

	class Camera
	{
	public:
		Camera(const Point3& lookFrom, const Point3& lookAt, const Vec3& vertUp, float vertFOV, float aspectRatio);
		~Camera();

		Ray GetRay(float u, float v) const;
		void SetFocalLength(const Point3& origin, const Point3& targett);

	private:
		Point3 m_origin;
		Point3 m_lowerLeftCorner;
		Vec3 m_horizontal;
		Vec3 m_vertical;
	};

}