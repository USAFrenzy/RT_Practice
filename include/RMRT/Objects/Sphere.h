#pragma once

#include <RMRT/Objects/HittableObject.h>
#include <RMRT/Bounds/AABB.h>
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
		bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;
		inline constexpr bool BoundingBox(float time0, float time1, AABB& outputBox) const override {
			outputBox = AABB(m_center - Vec3(m_radius, m_radius, m_radius), m_center + Vec3(m_radius, m_radius, m_radius));
			return true;
		}

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

		bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;
		bool BoundingBox(float time0, float time1, AABB& outputBox) const override;

		inline constexpr Point3 Center(float time) const
		{
			return m_center0 + ((time - m_time0) / m_timeDelta) * (m_centerDelta);
		}


	public:
		Point3 m_center0, m_center1;
		float m_time0, m_time1;
		float m_radius, m_radiusSquared;
		std::shared_ptr<Material> m_materialPtr;
		Point3 m_centerDelta;
		float m_timeDelta;
	};
}