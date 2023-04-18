
#include <RMRT/Materials/Dielectric.h>

namespace rmrt {
	DielectricMaterial::DielectricMaterial(float refractionIndex): m_refractiveIndex(refractionIndex) { }

	bool DielectricMaterial::Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const {
		attenuation = colorMap[ TempColor::white ];
		float refractionRatio { record.frontFace ? (1.0f / m_refractiveIndex) : m_refractiveIndex };
		Vec3 directionUnit { UnitVector(ray.Direction()) };
		// The next three lines solve for the angles required to know if  ray is inside the material or not; if it's inside, we must reflect the ray, else we refract
		// it
		float cosTheta { fmin(Dot(-directionUnit, record.normal), 1.0f) };
		float sinTheta { sqrt(1.0f - (cosTheta * cosTheta)) };

		Vec3 direction { ((refractionRatio * sinTheta > 1.0f) || (Reflectance(cosTheta, refractionRatio) > RandomDouble()))
			             ? Reflect(directionUnit, record.normal)
			             : Refract(directionUnit, record.normal, refractionRatio) };
		scattered = Ray(record.p, direction, ray.Time());
		return true;
	}

	float DielectricMaterial::RefractiveIndex() const {
		return m_refractiveIndex;
	}

	void DielectricMaterial::SetRefractiveIndex(float index) {
		m_refractiveIndex = index;
	}

	// This function uses Schlick's approximation for a reflectance factor
	float rmrt::DielectricMaterial::Reflectance(float cosine, float refIndex) {
		auto r0 { (1 - refIndex) / (1 + refIndex) };
		r0 *= r0;
		return r0 + (1.0f - r0) * pow((1.0f - cosine), 5.0f);
	}

}    // namespace rmrt