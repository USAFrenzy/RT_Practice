#pragma once

#include <RMRT/Materials/Material.h>

namespace rmrt {

	class MetalMaterial final  : public Material {
	public:
		MetalMaterial(const Color& albedo, float fuzz);
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const override;

	public:
		Color m_albedo;
		float m_fuzz;
	};

}