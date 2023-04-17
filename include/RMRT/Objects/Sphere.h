#pragma once

#include <RMRT/Objects/HittableObject.h>
#include <RMRT/Vec3.h>

namespace rmrt {

	class Sphere final : public HittableObject
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
		std::shared_ptr<Material> m_materialPtr;
	};

	class MovingSphere final : public HittableObject
	{

	public:
		MovingSphere();
		MovingSphere(Point3 center0, Point3 center1, float time0, float time1, float radius, std::shared_ptr<Material> material);

		virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;
		Point3 Center(float time) const;

	public:
		Point3 m_center0, m_center1;
		float m_time0,  m_time1;
		float m_radius, m_radiusSquared;
		std::shared_ptr<Material> m_materialPtr;
		Point3 m_centerDelta;
		float m_timeDelta;
	};
}