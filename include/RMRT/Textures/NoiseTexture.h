#pragma once

#include <RMRT/Noise/Perlin.h>
#include <RMRT/RMRT.h>
#include <RMRT/Textures/Texture.h>

namespace rmrt {

	class NoiseTexture: public Texture
	{
	  public:
		NoiseTexture(): m_scale(4.0f) { }
		NoiseTexture(float scale): m_scale(scale) { }

		inline virtual Color Value(float u, float v, const Point3& p) const override {
			return colorMap[ TempColor::white ] * 0.5f * (1.0f + m_noise.Noise(m_scale * p));
		}

	  private:
		float m_scale;
		PerlinNoise m_noise;
	};

	class TurbulentTexture: public Texture
	{
	  public:
		TurbulentTexture(): m_scale(4.0f) { }
		TurbulentTexture(float scale): m_scale(scale) { }

		inline virtual Color Value(float u, float v, const Point3& p) const override {
			return colorMap[ TempColor::white ] * m_noise.Turbulence(m_scale * p);
		}

	  private:
		float m_scale;
		PerlinNoise m_noise;
	};

}    // namespace rmrt
