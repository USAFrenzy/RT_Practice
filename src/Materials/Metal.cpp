
#include <RMRT/Materials/Metal.h>

namespace rmrt {

	MetalMaterial::MetalMaterial(const Color& albedo, float fuzz) : m_albedo(albedo), m_fuzz(fuzz < 1 ? fuzz : 1)
	{
	}

	bool MetalMaterial::Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const
	{
		Vec3 reflected{ Reflect(UnitVector(ray.Direction()), record.normal) };
		scattered = Ray(record.p, reflected + (m_fuzz*RandomInUnitSphere()));
		attenuation = m_albedo;
		return (Dot(scattered.Direction(), record.normal) > 0);
	}

}