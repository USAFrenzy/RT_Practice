#pragma once

#include <RMRT/Objects/HittableObject.h>
#include <RMRT/Textures/Texture.h>
#include <RMRT/RMRT.h>

namespace rmrt {

	struct HitRecord;

	class Material
	{
	  public:
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const = 0;
	};

}    // namespace rmrt
