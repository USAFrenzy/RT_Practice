#pragma once

#include <RMRT/Materials/Material.h>

namespace rmrt {

	class MetalMaterial : public Material {
	public:
		MetalMaterial(const Color& albedo, double fuzz);
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const override;

	public:
		Color m_albedo;
		double m_fuzz;
	};

}