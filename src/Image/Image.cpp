
#include <RMRT/Image/Image.h>

#include <iostream>

namespace rmrt {
	Image::Image(std::string fileName, double aspectRatio, int width)
		: m_name(fileName), m_aspectRatio(aspectRatio), m_width(width), m_height(static_cast<int>(width / aspectRatio)),
		m_maxDiffuseRays(50), m_samplesPerPixel(100), m_samplesIter(std::vector<int>{}), file(std::ofstream{})
	{
		m_samplesIter.resize(m_samplesPerPixel);
		for (auto& pos : m_samplesIter) m_samplesIter[pos] = pos;
		file.open(fileName, std::ios_base::trunc);
		WriteHeaderPPM();
	}

	Image::~Image()
	{
		file.flush();
		file.close();
	}

	void Image::SetDiffuseRayCount(int numberOfRays)
	{
		m_maxDiffuseRays = numberOfRays;
	}

	void Image::SetRaySampleCount(int numberOfSamples)
	{
		m_samplesPerPixel = numberOfSamples;
		if (m_samplesIter.capacity() < m_samplesPerPixel) {
			m_samplesIter.resize(m_samplesPerPixel);
			for (auto& pos : m_samplesIter) m_samplesIter[pos] = pos;
		}
	}

	void Image::SetDimensions(int width, int height) {
		m_width = width;
		m_height = height == 0 ? static_cast<int>(width / m_aspectRatio) : height;
		file.close();
		file.open(m_name, std::ios_base::trunc);
		WriteHeaderPPM(); // need to rewrite header for the new dimensions
	}

	void Image::WriteHeaderPPM() {
		if (file.is_open()) file.close();
		file.open(m_name, std::ios_base::trunc);
		std::string fileHeader{ "P3\n" };
		fileHeader.append(std::to_string(m_width)).append(" ").append(std::to_string(m_height)).append("\n255\n");
		file.write(fileHeader.data(), fileHeader.size());
		file.flush();
	}


	int Image::ImageWidth()
	{
		return m_width;
	}

	int Image::ImageHeight()
	{
		return m_height;
	}

	Color Image::RaySamples(const Camera& camera, const HittableList& world, int horizontalPixel, int verticalPixel) {
		Color pixelColor(0, 0, 0);
		std::for_each(std::execution::par, m_samplesIter.begin(), m_samplesIter.end(), [&](auto samples) {
			// 'u' and 'v' are the superimposed axes over the camera viewport axes
			auto u{ (horizontalPixel + RandomDouble()) / m_width };
			auto v{ (verticalPixel + RandomDouble()) / m_height };
			Ray ray{ camera.GetRay(u, v) };
			pixelColor += RayColor(ray, world, m_maxDiffuseRays);
			});
		return pixelColor;
	}

	void Image::WriteColor(const rmrt::Color& pixelColor)
	{
		auto scale{ 1.0 / m_samplesPerPixel };
		auto r{ std::sqrt(pixelColor.X() * scale) };
		auto g{ std::sqrt(pixelColor.Y() * scale) };
		auto b{ std::sqrt(pixelColor.Z() * scale) };
		// This basically does what the initial code in the 2.1 module of 'Raytracing In One Weekend' accomplished, 
		// except it now uses the ostream class to write to the console (This is from module 3.3)
		//
		// The addition of the above lines with the scale and the function Clamp() is found from module 7.2
		fileTempBuff.clear();
		fileTempBuff.append(std::to_string(static_cast<int>(rgb_factor * rmrt::Clamp(r, 0.0, 0.999))))
			.append(" ")
			.append(std::to_string(static_cast<int>(rgb_factor * rmrt::Clamp(g, 0.0, 0.999))))
			.append(" ")
			.append(std::to_string(static_cast<int>(rgb_factor * rmrt::Clamp(b, 0.0, 0.999))))
			.append("\n");
		file.write(fileTempBuff.data(), fileTempBuff.size());
		file.flush();
	}

	void Image::TraceImage(const Camera& camera, const HittableList& world) {
		for (auto i{ m_height - 1 }; i >= 0; --i) {
			// Adding a progress indicator
			std::cerr << "\rScanlines Remaining: " << i << ' ' << std::flush;
			for (auto j{ 0 }; j < m_width; ++j) {
				WriteColor(RaySamples(camera, world, j, i));
			}
		}
		// Progress completed
		std::cerr << "\nDone.\n";
	}

}