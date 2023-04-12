#pragma once

#include <RMRT/Objects/HittableObject.h>
#include <RMRT/Vec3.h>

namespace rmrt {

	class Sphere : public HittableObject
	{
	public:
		Sphere();
		Sphere(Point3 center, float radius, std::shared_ptr<Material> material);
		~Sphere();

		void SetCenter(const Point3& center);
		const Point3& GetCenter() const;
		void SetRadius(const float& radius);
		const float& GetRadius() const;
		virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;

	private:
		Point3 m_center;
		float m_radius;
		float m_radiusSquared;
		float m_lengthSquared;
		std::shared_ptr<Material> m_materialPtr;
	};
}