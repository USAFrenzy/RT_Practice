#pragma once

#include <RMRT/RMRT.h>

namespace rmrt {

	class Camera
	{
	public:
		Camera();
		Camera(float aspectRatio, float viewPortHeight, float viewPortWidth, float focalLength);
		~Camera();

		Ray GetRay(float u, float v) const;
		void SetFocalLength(float focalLength);


	private:
		Point3 m_origin;
		Point3 m_lowerLeftCorner;
		Vec3 m_horizontal;
		Vec3 m_vertical;
	};

}