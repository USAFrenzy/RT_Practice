
#include <RMRT/Objects/Sphere.h>

namespace rmrt {
	Sphere::Sphere()
	{
	}

	Sphere::Sphere(Point3 center, double radius) : m_center(center), m_radius(radius)
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

	void Sphere::SetRadius(const double& radius)
	{
		m_radius = radius;
	}

	const double& Sphere::GetRadius() const
	{
		return m_radius;
	}

	bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& record) const
	{
		Vec3 originCenter{ ray.Origin() - m_center };
		// Both 'a' and 'c' were simplified in module 6.2 due to the vector attribute that states: 
		// A vector dot with itself  == length^2 of that vector
		// 'b' was simplified due to '2' cancelling out ==> discriminant and return check was simplified as well
		auto a{ ray.Direction().LengthSquared() };
		auto bHalf{ Dot(originCenter, ray.Direction()) };
		auto c{ originCenter.LengthSquared() - (m_radius * m_radius) };

		auto discriminant{ (bHalf * bHalf) - (a * c) };
		if (discriminant < 0) return false;
		auto sqrtDiscriminant{ std::sqrt(discriminant) };

		// The new portion as of module 6.3, the following finds the nearest root that lies within the min/max range paramaters
		auto root{ (-bHalf - sqrtDiscriminant) / a };
		if (root < tMin || tMax < root) {
			root = (-bHalf + sqrtDiscriminant) / a;
			if (root < tMin || tMax < root) return false;
		}

		record.t = root;
		record.p = ray.At(record.t);
		Vec3 outwardNormal{ (record.p - m_center) / m_radius };
		record.SetFaceNormal(ray, outwardNormal);

		return true;
	}
}