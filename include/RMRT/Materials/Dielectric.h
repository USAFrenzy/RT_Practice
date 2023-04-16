#pragma once

#include <RMRT/Materials/Material.h>

namespace rmrt {

	class DielectricMaterial final  : public Material {
		
	public:
		DielectricMaterial(float refractionIndex);

		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const override;
		float RefractiveIndex() const;
		void SetRefractiveIndex(float index);
		static float Reflectance(float cosine, float refIndex);

	private:
		float m_refractiveIndex;
	};
}