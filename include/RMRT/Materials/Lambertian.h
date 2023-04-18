#pragma once

#include <RMRT/Materials/Material.h>

namespace rmrt {

	class LambertianMaterial final: public Material
	{
	  public:
		LambertianMaterial(const Color& albedo);
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const override;

	  public:
		Color m_albedo;
	};

}    // namespace rmrt