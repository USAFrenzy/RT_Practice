#pragma once

#include <RMRT/Objects/HittableObject.h>
#include <RMRT/RMRT.h>
#include <RMRT/Textures/Texture.h>

namespace rmrt {

	struct HitRecord;

	class Material
	{
	  public:
		virtual bool Scatter(const rmrt::Ray& ray, const rmrt::HitRecord& record, rmrt::Color& attenuation, rmrt::Ray& scattered) const = 0;
	};

}    // namespace rmrt
