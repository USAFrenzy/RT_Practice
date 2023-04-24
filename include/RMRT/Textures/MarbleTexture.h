#pragma once

#include <RMRT/Noise/Perlin.h>
#include <RMRT/RMRT.h>
#include <RMRT/Textures/Texture.h>

namespace rmrt {

	class MarbleTexture: public Texture
	{
	  public:
		MarbleTexture(): m_scale(4.0f) { }
		MarbleTexture(float scale): m_scale(scale) { }

		inline virtual Color Value(float u, float v, const Point3& p) const override {
			return colorMap[ TempColor::white ] * 0.5f * (1 + sin(m_scale * p.Z() + 10.0f * m_noise.Turbulence(p)));
		}

	  private:
		float m_scale;
		PerlinNoise m_noise;
	};

}    // namespace rmrt
