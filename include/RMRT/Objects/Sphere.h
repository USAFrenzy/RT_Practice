#pragma once

#include <RMRT/Objects/HittableObject.h>
#include <RMRT/Vec3.h>

namespace rmrt {

	class Sphere : public HittableObject
	{
	public:
		Sphere();
		Sphere(Point3 center, double radius);
		~Sphere();

		void SetCenter(const Point3& center);
		const Point3& GetCenter() const;
		void SetRadius(const double& radius);
		const double& GetRadius() const;
		virtual bool Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const override;

	private:
		Point3 m_center;
		double m_radius;

	};
}