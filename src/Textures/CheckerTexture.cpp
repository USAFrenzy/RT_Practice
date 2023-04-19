
#include <RMRT/Textures/CheckerTexture.h>

namespace rmrt {

	CheckerTexture::CheckerTexture() { }

	CheckerTexture::CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd): m_even(even), m_odd(odd) { }

	CheckerTexture::CheckerTexture(Color color1, Color color2): m_even(std::make_shared<SolidColor>(color1)), m_odd(std::make_shared<SolidColor>(color2)) { }

	Color CheckerTexture::Value(float u, float v, const Point3& p) const {
		auto sines { sin(10 * p.X()) * sin(10 * p.Y()) * sin(10 * p.Z()) };
		return sines < 0 ? m_odd->Value(u, v, p) : m_even->Value(u, v, p);
	}

}    // namespace rmrt
