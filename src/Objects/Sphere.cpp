
#include <RMRT/Objects/Sphere.h>

namespace rmrt {
	Sphere::Sphere()
	{
	}

	Sphere::Sphere(Point3 center, float radius, std::shared_ptr<Material> material) : m_center(center), m_radius(radius), m_radiusSquared(m_radius*m_radius), m_materialPtr(material)
	{
	}

	Sphere::~Sphere()
	{
	}

	void Sphere::SetCenter(const Point3& center)
	{
		m_center = center;
	}

	const Point3& Sphere::GetCenter() const
	{
		return m_center;
	}

	void Sphere::SetRadius(const float& radius)
	{
		m_radius = radius;
	}

	const float& Sphere::GetRadius() const
	{
		return m_radius;
	}

	bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
	{
		Vec3 originCenter{ ray.Origin() - m_center };
		// Both 'a' and 'c' were simplified in module 6.2 due to the vector attribute that states: 
		// A vector dot with itself  == length^2 of that vector
		// 'b' was simplified due to '2' canceling out ==> discriminant and return check was simplified as well
		auto c{ originCenter.LengthSquared() - m_radiusSquared };
		const auto& rayDirection {ray.Direction()};
		auto a{ rayDirection.LengthSquared() };
		auto bHalf{ Dot(originCenter, rayDirection) };
		auto discriminant{ (bHalf * bHalf) - (a * c) };
		if (discriminant < 0) return false;
		auto sqrtDiscriminant{ std::sqrt(discriminant) };

		// The new portion as of module 6.3, the following finds the nearest root that lies within the min/max range parameters
		auto root{ (-bHalf - sqrtDiscriminant) / a };
		if (root < tMin || tMax < root) {
			root = (-bHalf + sqrtDiscriminant) / a;
			if (root < tMin || tMax < root) return false;
		}

		record.t = root;
		record.p = ray.At(record.t);
		Vec3 outwardNormal{ (record.p - m_center) / m_radius };
		record.SetFaceNormal(ray, outwardNormal);
		record.materialPtr = m_materialPtr;

		return true;
	}

	MovingSphere::MovingSphere()
	{
	}

	MovingSphere::MovingSphere(Point3 center0, Point3 center1, float time0, float time1, float radius, std::shared_ptr<Material> material)
		: m_center0(center0), m_center1(center1), m_time0(time0), m_time1(time1), m_radius(radius), m_radiusSquared(radius*radius), m_materialPtr(material), m_centerDelta(center1-center0), m_timeDelta(time1-time0)
	{
	}

	bool MovingSphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
	{
		const auto& rayTime { ray.Time() };
		Vec3 originCenter{ ray.Origin() - Center(rayTime)};
		auto c{ originCenter.LengthSquared() - m_radiusSquared };
		const auto& rayDirection{ ray.Direction() };
		auto a{ rayDirection.LengthSquared() };
		auto bHalf{ Dot(originCenter, rayDirection) };
		auto discriminant{ (bHalf * bHalf) - (a * c) };
		if (discriminant < 0) return false;
		auto sqrtDiscriminant{ std::sqrt(discriminant) };
		auto root{ (-bHalf - sqrtDiscriminant) / a };
		if (root < tMin || tMax < root) {
			root = (-bHalf + sqrtDiscriminant) / a;
			if (root < tMin || tMax < root) return false;
		}
		record.t = root;
		record.p = ray.At(record.t);
		Vec3 outwardNormal{ (record.p - Center(rayTime)) / m_radius };
		record.SetFaceNormal(ray, outwardNormal);
		record.materialPtr = m_materialPtr;

		return true;
	}

	bool MovingSphere::BoundingBox(float time0, float time1, AABB& outputBox) const
	{
		AABB box0{ Center(m_time0) - Vec3(m_radius, m_radius, m_radius), Center(m_time0) + Vec3(m_radius, m_radius, m_radius) };
		AABB box1{ Center(m_time1) - Vec3(m_radius, m_radius, m_radius), Center(m_time1) + Vec3(m_radius, m_radius, m_radius) };
		outputBox = SurroundingBox(box0, box1);
		return true;
	}


}