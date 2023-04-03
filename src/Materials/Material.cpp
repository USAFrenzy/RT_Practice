#include <RMRT/Materials/Material.h>

namespace rmrt {

	Lambertian::Lambertian(const Color& albedo) : m_albedo(albedo)
	{
	}

	bool Lambertian::Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const
	{
		auto scatterDirection{ record.normal + RandomUnitVector() };
		// As noted in the book, this next line catches sum 0 scatter vectors and sets them to the normalized vector instead
		if (scatterDirection.NearZero()) scatterDirection = record.normal;
		scattered = Ray(record.p, scatterDirection);
		attenuation = m_albedo;
		return true;
	}

	MetalMaterial::MetalMaterial(const Color& albedo) : m_albedo(albedo)
	{
	}

	bool MetalMaterial::Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const
	{
		Vec3 reflected{ Reflect(UnitVector(ray.Direction()), record.normal) };
		scattered = Ray(record.p, reflected);
		attenuation = m_albedo;
		return (Dot(scattered.Direction(), record.normal) > 0);
	}

}