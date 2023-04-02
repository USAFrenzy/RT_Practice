#pragma once

#include <RMRT/Ray.h>

namespace rmrt {

	struct HitRecord
	{
		Point3 p;
		Vec3 normal;
		double t;
		bool frontFace;

		// This function simply compares whether or not the vector in question points with or against the ray direction and stores the 
		// relative information for the face of the object, whether it's a front facing ray hit or not and if it's not, stores the vector as a 
		// normal with the opposite direction of the ray.
		inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
			frontFace = Dot(ray.Direction(), outwardNormal) < 0;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};

	class HittableObject
	{
	public:
		virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const = 0;
	};
}