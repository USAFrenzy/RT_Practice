#pragma once

#include <RMRT/RMRT.h>
#include <RMRT/Objects/HittableObject.h>

namespace rmrt {

	struct HitRecord;

	class Material {
	public:
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const = 0;
	};

	class Lambertian : public Material {
	public:
		Lambertian(const Color& albedo);
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const override;

	public:
		Color m_albedo;
	};

	class MetalMaterial : public Material {
	public:
		MetalMaterial(const Color& albedo);
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const override;

	public:
		Color m_albedo;
	};

}

