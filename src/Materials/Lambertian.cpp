
#include <RMRT/Materials/Lambertian.h>

namespace rmrt {

	LambertianMaterial::LambertianMaterial(const Color& albedo): m_albedo(std::make_shared<SolidColor>(albedo)) { }

	LambertianMaterial::LambertianMaterial(std::shared_ptr<Texture> albedo ) : m_albedo(albedo) {}

	bool LambertianMaterial::Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const {
		auto scatterDirection { record.p + record.normal + RandomUnitVector() };
		// As noted in the book, this next line catches sum 0 scatter vectors and sets them to the normalized vector instead
		if( scatterDirection.NearZero() ) scatterDirection = record.normal;
		scattered   = Ray(record.p, (scatterDirection - record.p), ray.Time());
		attenuation = m_albedo->Value(record.textureU, record.textureV, record.p);
		return true;
	}

}    // namespace rmrt