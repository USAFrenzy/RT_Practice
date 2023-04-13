
#include <RMRT/Image/Image.h>

#include <iostream>
#include <charconv>

namespace rmrt {

	Image::Image(std::string_view fileName, float aspectRatio, int width)
		: m_name(fileName), m_aspectRatio(aspectRatio), m_width(width), m_height(static_cast<int>(width / aspectRatio)),
		m_maxDiffuseRays(50), m_samplesPerPixel(100), m_samplesIter(std::vector<int>{}), m_file(std::ofstream{}), m_scale(1.0f / m_samplesPerPixel)
	{
		m_samplesIter.resize(m_samplesPerPixel);
		for (auto& pos : m_samplesIter) m_samplesIter[pos] = pos;
		m_file.open(fileName.data(), std::ios_base::trunc);
		WriteHeaderPPM();
	}

	Image::~Image()
	{
		m_file.flush();
		m_file.close();
	}

	void Image::SetDiffuseRayCount(int numberOfRays)
	{
		m_maxDiffuseRays = numberOfRays;
	}

	void Image::SetRaySampleCount(int numberOfSamples)
	{
		m_samplesPerPixel = numberOfSamples;
		m_scale = (1.0f / m_samplesPerPixel);
		if (m_samplesIter.capacity() < m_samplesPerPixel) {
			m_samplesIter.resize(m_samplesPerPixel);
			for (auto& pos : m_samplesIter) m_samplesIter[pos] = pos;
		}
	}

	void Image::SetDimensions(int width, int height) {
		m_width = width;
		m_height = height == 0 ? static_cast<int>(width / m_aspectRatio) : height;
		m_file.close();
		m_file.open(m_name, std::ios_base::trunc);
		WriteHeaderPPM(); // need to rewrite header for the new dimensions
	}

	void Image::WriteHeaderPPM() {
		if (m_file.is_open()) m_file.close();
		m_file.open(m_name, std::ios_base::trunc);
		std::string fileHeader{ "P3\n" };
		fileHeader.append(std::to_string(m_width)).append(" ").append(std::to_string(m_height)).append("\n255\n");
		m_file.write(fileHeader.data(), fileHeader.size());
		m_file.flush();
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
			// 'u' and 'v' are the superimposed axes over the camera view port axes
			auto u{ (horizontalPixel + RandomDouble()) / m_width };
			auto v{ (verticalPixel + RandomDouble()) / m_height };
			Ray ray{ camera.GetRay(u, v) };
			pixelColor += RayColor(ray, world, m_maxDiffuseRays);
			});
		return pixelColor;
	}

	void Image::WriteColor(const rmrt::Color& pixelColor)
	{
		const auto data{ m_buffer.data() };
		std::memset(data, '\0', 16);
		Vec3 rgbVec{ pixelColor };
		ScaleVecViaClamp(rgbVec, 0.0f, 0.999f);
		// Eventually, for shits and giggles, this will be mapped to a 2D array that will be the size of the image and once the render is 
		// finished, the contents of the 2D array will be written to the file directly instead of writing to the file and flushing every call
		auto pos{ std::to_chars(data, data + 16, static_cast<int>(rgbVec.X())).ptr - data };
		m_buffer[pos] = ' ';
		++pos;
		pos = std::to_chars(data + pos, data + 16, static_cast<int>(rgbVec.Y())).ptr - data;
		m_buffer[pos] = ' ';
		++pos;
		pos = std::to_chars(data + pos, data + 16, static_cast<int>(rgbVec.Z())).ptr - data;
		m_buffer[pos] = '\n';
		m_file.write(data, ++pos);
		m_file.flush();
	}

	// This currently uses parallel execution for the pixel sampling, however, parallelizing on scan-line height 
	// would be better suited here -> instead of using std::for_each, it might be better to use std::jthreads here.
	// This also means that writing the pixel color to either the file or a 2D array as noted above will need to 
	// ensure that no data races occur when synchronizing the result from each thread.
	void Image::TraceImage(const Camera& camera, const HittableList& world) {
		for (auto i{ m_height - 1 }; i >= 0; --i) {
			// Adding a progress indicator
			for (auto j{ 0 }; j < m_width; ++j) {
				std::cerr << "\rScan-lines Remaining: " << i
					<< "    " << "Current Pixel: [ " << j + 1 << " / " << m_width << " ]" << "  " << std::flush;
				WriteColor(RaySamples(camera, world, j, i));
			}
		}
	}

	void Image::ScaleVecViaClamp(Vec3& vec, float min, float max) {
		for (auto& val : vec.e) val = sqrt(val *= m_scale);
		vec.e[0] = rgb_factor * (vec.e[0]  < min ? min : vec.e[0] > max ? max : vec.e[0]);
		vec.e[1] = rgb_factor * (vec.e[1]  < min ? min : vec.e[1] > max ? max : vec.e[1]);
		vec.e[2] = rgb_factor * (vec.e[2]  < min ? min : vec.e[2] > max ? max : vec.e[2]);
	}

	int Image::RaySampleCount() { return m_samplesPerPixel; }

	int Image::DiffuseRayCount() { return m_maxDiffuseRays; }


}