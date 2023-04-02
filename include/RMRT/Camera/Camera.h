#pragma once

#include <RMRT/RMRT.h>

namespace rmrt {

	class Camera
	{
	public:
		Camera();
		Camera(double aspectRatio, double viewPortHeight, double viewPortWidth, double focalLength);
		~Camera();

		Ray GetRay(double u, double v) const;

	private:
		Point3 m_origin;
		Point3 m_lowerLeftCorner;
		Vec3 m_horizontal;
		Vec3 m_vertical;
	};

}