
#include <RMRT/Ray.h>

#include <iostream>

int main()
{

	// Image
	constexpr auto aspectRatio{ 16.0 / 9.0 };  // 16:9
	constexpr int imgWidth{ 400 };
	constexpr int imgHeight{ static_cast<int>(imgWidth / aspectRatio) };

	// Camera
	auto viewportHeight{ 2.0 };
	auto viewportWidth{ viewportHeight * aspectRatio };
	auto focalLength{ 1.0 };

	auto origin{ rmrt::Point3(0,0,0) };
	auto horizontal{ rmrt::Vec3(viewportWidth, 0,0) };
	auto vertical{ rmrt::Vec3(0,viewportHeight, 0) };
	auto lowerLeftCorner{ (origin - horizontal / 2) - (vertical / 2) - rmrt::Vec3(0,0,focalLength) };


	// Render
	std::cout << "P3\n" << imgWidth << " " << imgHeight << "\n255\n";

	// Extracting the constant variables from within the loop for readablity
	constexpr auto b{ 0.25 };
	constexpr auto cWidth{ imgWidth - 1 };
	constexpr auto cHeight{ imgHeight - 1 };

	for (auto i{ cHeight }; i >= 0; --i) {
		// Adding a progress indicator
		std::cerr << "\rScanlines Remaining: " << i << ' ' << std::flush;

		for (auto j{ 0 }; j < imgWidth; ++j) {
			// 'u' and 'v' are the superimposed axes over the camera viewport axes
			auto u{ static_cast<double>(j) / cWidth };
			auto v{ static_cast<double>(i) / cHeight };
			auto rayDirection{ (u * horizontal) + (v * vertical) - origin };

			rmrt::Ray ray{ origin, lowerLeftCorner + rayDirection };
			rmrt::Color pixelColor{ ray.RayColor(ray) };
			rmrt::WriteColor(std::cout, pixelColor);
		}
	}
	// Progress completed
	std::cerr << "\nDone.\n";
}