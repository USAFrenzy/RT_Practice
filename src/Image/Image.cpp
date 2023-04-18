
#include <RMRT/Image/Image.h>

#include <charconv>
#include <iostream>

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define VC_EXTRALEAN
	#include <Windows.h>
	#include <io.h>
#endif

namespace rmrt {

	Image::Image(std::string_view fileName, float aspectRatio, int width)
		: m_name(fileName), m_aspectRatio(aspectRatio), m_width(width), m_height(static_cast<int>(width / aspectRatio)), m_maxDiffuseRays(50),
		  m_samplesPerPixel(100), m_samplesIter(std::vector<int> {}), m_file(std::ofstream {}), m_scale(1.0f / m_samplesPerPixel),
		  m_buffer(std::array<char, img_helper::BUFF_SIZE> {}), m_tracker(ProgressTracker {}), m_imgMatrix(std::vector<std::vector<std::string>> {}) {
		m_samplesIter.resize(m_samplesPerPixel);
		for( auto& pos: m_samplesIter ) m_samplesIter[ pos ] = pos;
		m_file.open(fileName.data(), std::ios_base::trunc);
		WriteHeaderPPM();
		ResizeImageMatrix();
	}

	Image::~Image() {
		m_file.flush();
		m_file.close();
	}

	void rmrt::Image::ResizeImageMatrix() {
		m_imgMatrix.resize(m_height);
		for( auto& scanline: m_imgMatrix ) {
				scanline.resize(m_width);
			}
		for( auto& scanline: m_imgMatrix ) {
				for( auto& pixel: scanline ) {
						pixel.reserve(24);
					}
			}
	}

	void Image::SetDiffuseRayCount(int numberOfRays) {
		m_maxDiffuseRays = numberOfRays;
	}

	void Image::SetRaySampleCount(int numberOfSamples) {
		m_samplesPerPixel = numberOfSamples;
		m_scale           = (1.0f / m_samplesPerPixel);
		m_samplesIter.resize(m_samplesPerPixel);
		for( auto& pos: m_samplesIter ) m_samplesIter[ pos ] = pos;
	}

	void Image::SetDimensions(int width, int height) {
		m_width  = width;
		m_height = height == 0 ? static_cast<int>(width / m_aspectRatio) : height;
		m_file.close();
		m_file.open(m_name, std::ios_base::trunc);
		WriteHeaderPPM();    // need to rewrite header for the new dimensions
		ResizeImageMatrix();
	}

	void Image::WriteHeaderPPM() {
		if( m_file.is_open() ) m_file.close();
		m_file.open(m_name, std::ios_base::trunc);
		std::string fileHeader { "P3\n" };
		fileHeader.append(std::to_string(m_width)).append(" ").append(std::to_string(m_height)).append("\n255\n");
		m_file.write(fileHeader.data(), fileHeader.size());
		m_file.flush();
	}

	int Image::ImageWidth() {
		return m_width;
	}

	int Image::ImageHeight() {
		return m_height;
	}

	Color Image::RaySamples(const Camera& camera, const HittableList& world, int horizontalPixel, int verticalPixel) {
		Color pixelColor(0, 0, 0);
		std::for_each(std::execution::par, m_samplesIter.begin(), m_samplesIter.end(), [ & ](auto samples) {
			// 'u' and 'v' are the superimposed axes over the camera view port axes
			auto u { (horizontalPixel + RandomDouble()) / m_width };
			auto v { (verticalPixel + RandomDouble()) / m_height };
			Ray ray { camera.GetRay(u, v) };
			pixelColor += RayColor(ray, world, m_maxDiffuseRays);
		});
		return pixelColor;
	}

	void Image::WriteColor(const rmrt::Color& pixelColor, int horizontalPixel, int verticalPixel) {
		namespace ih = img_helper;
		const auto data { m_buffer.data() };
		std::memset(data, '\0', ih::BUFF_SIZE);
		Vec3 rgbVec { pixelColor };
		ScaleVecViaClamp(rgbVec, 0.0f, 0.999f);
		auto pos { std::to_chars(data, data + ih::BUFF_SIZE, static_cast<int>(rgbVec.X())).ptr - data };
		m_buffer[ pos ] = ' ';
		++pos;
		pos             = std::to_chars(data + pos, data + ih::BUFF_SIZE, static_cast<int>(rgbVec.Y())).ptr - data;
		m_buffer[ pos ] = ' ';
		++pos;
		pos             = std::to_chars(data + pos, data + ih::BUFF_SIZE, static_cast<int>(rgbVec.Z())).ptr - data;
		m_buffer[ pos ] = '\n';
		m_imgMatrix[ verticalPixel ][ horizontalPixel ].append(std::move(std::string { data, static_cast<size_t>(++pos) }));
	}
	void rmrt::Image::PrintImageToFile() {
		std::string tmp;
		tmp.reserve(static_cast<size_t>(m_width) * m_height * 12);
		for( auto i { m_imgMatrix.size() - 1 }; i > 0; --i ) {
				for( const auto& pixel: m_imgMatrix[ i ] ) {
						tmp.append(pixel);
					}
			}
		m_file.write(tmp.data(), tmp.size());
		m_file.flush();
	}
	// This currently uses parallel execution for the pixel sampling, however, parallelizing on scan-line height
	// would be better suited here -> instead of using std::for_each, it might be better to use std::jthreads here.
	// This also means that writing the pixel color to either the file or a 2D array as noted above will need to
	// ensure that no data races occur when synchronizing the result from each thread.
	void Image::TraceImage(const Camera& camera, const HittableList& world) {
		auto startTime { std::chrono::steady_clock::now() };
		for( int i = m_height - 1; i >= 0; --i ) {
				for( int j = 0; j < m_width; ++j ) {
						// Adding a progress indicator
						m_tracker.PrintProgress(m_height, m_width, j, i, startTime);
						// Sample the rays for the current pixel and write the RGB value to the file
						WriteColor(RaySamples(camera, world, j, i), j, i);
					}
			}
	}

	void Image::ScaleVecViaClamp(Vec3& vec, float min, float max) {
		for( auto& val: vec.e ) val = sqrt(val *= m_scale);
		vec.e[ 0 ] = rgb_factor * (vec.e[ 0 ] < min ? min : vec.e[ 0 ] > max ? max : vec.e[ 0 ]);
		vec.e[ 1 ] = rgb_factor * (vec.e[ 1 ] < min ? min : vec.e[ 1 ] > max ? max : vec.e[ 1 ]);
		vec.e[ 2 ] = rgb_factor * (vec.e[ 2 ] < min ? min : vec.e[ 2 ] > max ? max : vec.e[ 2 ]);
	}

	int Image::RaySampleCount() {
		return m_samplesPerPixel;
	}

	int Image::DiffuseRayCount() {
		return m_maxDiffuseRays;
	}

	void rmrt::Image::ProgressTracker::EstimateTimeLeft(int currentScanLine, int totalScanLines, const std::chrono::steady_clock::time_point& startTime) {
		auto scanLinesCompleted { static_cast<double>(totalScanLines - currentScanLine) };
		auto remainingScanLines { totalScanLines - scanLinesCompleted };
		double avgElapsedSeconds { std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count() / scanLinesCompleted };
		double totalSeconds = avgElapsedSeconds * remainingScanLines;
		m_hours             = totalSeconds / 3600;
		m_minutes           = static_cast<double>((static_cast<size_t>(totalSeconds) % 3600) / 60);
		m_seconds           = static_cast<double>(static_cast<size_t>(totalSeconds) % 60);
	}

	std::string rmrt::Image::ProgressTracker::TimeLeftStr(int currentScanLine, int totalScanLines, const std::chrono::steady_clock::time_point& startTime) {
		EstimateTimeLeft(currentScanLine, totalScanLines, startTime);
		std::string tmp;
		tmp.append(std::to_string(static_cast<int>(m_hours))).append("h ");
		tmp.append(std::to_string(static_cast<int>(m_minutes))).append("m ");
		tmp.append(std::to_string(static_cast<int>(m_seconds))).append("s ");
		return tmp;
	}

	void rmrt::Image::ProgressTracker::PrintProgress(int totalScanLines, int totalWidth, int pixelX, int pixelY, const std::chrono::steady_clock::time_point& startTime) {
		std::string progressLine;
#ifdef _WIN32
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
		GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo);
		// Create the current progress string and print it to the console
		progressLine = "\rScan-lines Remaining: " + std::to_string(pixelY) + "    " + "Current Pixel: [ " + std::to_string(pixelX + 1) + " / " +
		               std::to_string(totalWidth) + " ]   " + "\nEstimated Time Left: [" + TimeLeftStr(pixelY, totalScanLines, startTime) + "]   ";
		WriteConsole(consoleHandle, progressLine.c_str(), static_cast<DWORD>(progressLine.size()), NULL, NULL);
		// Move the cursor back to the beginning of the current progress output
		if( (pixelY > 0) || (pixelX < totalWidth - 1) ) {
				COORD newPos = { 0, consoleInfo.dwCursorPosition.Y };
				SetConsoleCursorPosition(consoleHandle, newPos);
		} else {
				WriteConsole(consoleHandle, "\n", static_cast<DWORD>(1), NULL, NULL);
			}
#else
		// Store the current cursor position
		auto cursorPosition = std::cout.tellp();
		// Clear the current line
		std::cout << "\033[2K";
		// Move the cursor to the beginning of the line
		std::cout << "\033[1G";
		// Output the updated progress of the current scan-line and pixel position
		std::cerr << "Scan-lines Remaining: " << pixelY << "    "
				  << "Current Pixel: [ " << pixelX + 1 << " / " << totalWidth << " ]   ";
		// Output the estimated time left on a new line
		std::string timeLine = " Estimated Time Left: [" + TimeLeftStr(pixelY, totalScanLines, startTime) + "]   \n";
		std::cerr << timeLine << std::flush;
		// Move the cursor back to the stored position
		if( (pixelY > 0) || (pixelX < totalWidth - 1) ) {
				std::cout.seekp(cursorPosition);
		} else {
				std::cout << "\n";
			}
#endif
	}

}    // namespace rmrt