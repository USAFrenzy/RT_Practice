#pragma once

#include <RMRT/RMRT.h>
#include <RMRT/Textures/Texture.h>

namespace rmrt {

	class ImageTexture: public Texture
	{
	  public:
		constexpr static int bytesPerPixel { 3 };

		ImageTexture();
		ImageTexture(std::string_view fileName);
		~ImageTexture();

		virtual Color Value(float u, float v, const Point3& p) const override;

	  private:
		unsigned char* m_data;
		int m_width;
		int m_height;
		int m_bytesPerScanline;
	};

}    // namespace rmrt
