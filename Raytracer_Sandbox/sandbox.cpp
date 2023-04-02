
#include <RMRT/RMRT.h>
#include <RMRT/Objects/HittableList.h>
#include <RMRT/Objects/Sphere.h>
#include <RMRT/Camera/Camera.h>

#include <iostream>

int main()
{

	// Image
	constexpr auto aspectRatio{ 16.0 / 9.0 };  // 16:9
	constexpr int imgWidth{ 400 };
	constexpr int imgHeight{ static_cast<int>(imgWidth / aspectRatio) };
	constexpr int samplesPerPixel{ 100 };

	// World
	rmrt::HittableList world{};
	world.Store(std::make_shared<rmrt::Sphere>(rmrt::Point3(0, 0, -1), 0.5));
	world.Store(std::make_shared<rmrt::Sphere>(rmrt::Point3(0, -100.5, -1), 100));

	// Camera
	rmrt::Camera camera{};

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
			rmrt::Color pixelColor(0, 0, 0);
			for (int k{ 0 }; k < samplesPerPixel; ++k) {
				// 'u' and 'v' are the superimposed axes over the camera viewport axes
				auto u{ (j + rmrt::RandomDouble()) / cWidth };
				auto v{ (i + rmrt::RandomDouble()) / cHeight };
				rmrt::Ray ray{ camera.GetRay(u, v) };
				pixelColor += world.RayColor(ray, world);
			}
			rmrt::WriteColor(std::cout, pixelColor, samplesPerPixel);
		}
	}
	// Progress completed
	std::cerr << "\nDone.\n";
}