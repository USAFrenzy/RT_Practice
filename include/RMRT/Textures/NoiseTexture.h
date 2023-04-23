#pragma once

#include <RMRT/Noise/Perlin.h>
#include <RMRT/RMRT.h>
#include <RMRT/Textures/Texture.h>

namespace rmrt {

	class NoiseTexture: public Texture
	{
	  public:
		NoiseTexture() { }
		NoiseTexture(float scale): m_scale(scale) { }

		inline virtual Color Value(float u, float v, const Point3& p) const override {
			return colorMap[ TempColor::white ] * m_noise.Noise(m_scale * p);
		}

	  private:
		PerlinNoise m_noise;
		float m_scale;
	};

}    // namespace rmrt
