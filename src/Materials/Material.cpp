#include <RMRT/Materials/Material.h>

// This cpp file should be done away with once the Lambertian class is in its own file as well
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

}