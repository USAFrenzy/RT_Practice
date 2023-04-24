
#include <RMRT/Textures/ImageTexture.h>

#ifdef _MSC_VER
	#pragma warning(push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#include <vendor/stb/stb_image.h>

#ifdef _MSC_VER
	#pragma warning(pop)
#endif

namespace rmrt {
	ImageTexture::ImageTexture(): m_data(nullptr), m_width(0), m_height(0), m_bytesPerScanline(0) { }

	ImageTexture::ImageTexture(std::string_view fileName): m_data(nullptr), m_width(0), m_height(0), m_bytesPerScanline(0) {
		auto componentsPerPixel { bytesPerPixel };
		m_data = stbi_load(fileName.data(), &m_width, &m_height, &componentsPerPixel, componentsPerPixel);
		if( !m_data ) {
				printf("Error: Unable To Load Texture Image File: '%s'.\n", fileName.data());
				m_width = m_height = 0;
		}
		m_bytesPerScanline = bytesPerPixel * m_width;
	}

	ImageTexture::~ImageTexture() {
		delete m_data;
	}

	Color ImageTexture::Value(float u, float v, const Point3& p) const {
		// Return Cyan if no valid texture data is present
		if( m_data == nullptr ) return Color(0.0f, 1.0f, 1.0f);

		// Clamp input texture coords between [0, 1] x [1, 0]
		u = Clamp(u, 0.0f, 1.0f);
		v = 1.0f - Clamp(v, 0.0f, 1.0f);    // Flip V to image coords
		auto i { static_cast<int>(u * m_width) };
		auto j { static_cast<int>(v * m_height) };

		// Clamp int mapping due to coords < 1.0
		if( i >= m_width ) i = m_width - 1;
		if( j >= m_height ) j = m_height - 1;

		const auto colorScale { 1.0f / 255.0f };
		auto pixel { m_data + (j * m_bytesPerScanline) + (i * bytesPerPixel) };
		return Color(colorScale * pixel[ 0 ], colorScale * pixel[ 1 ], colorScale * pixel[ 2 ]);
	}

}    // namespace rmrt
