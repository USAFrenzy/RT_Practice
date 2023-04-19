#pragma once

#include <RMRT/Textures/Texture.h>

namespace rmrt {

	class CheckerTexture: public Texture
	{
	  public:
		CheckerTexture();
		CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd);
		CheckerTexture(Color color1, Color color2);

		virtual Color Value(float u, float v, const Point3& p) const override;

	  private:
		std::shared_ptr<Texture> m_odd;
		std::shared_ptr<Texture> m_even;
	};

}    // namespace rmrt
