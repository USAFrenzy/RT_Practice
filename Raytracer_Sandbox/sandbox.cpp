
#include <RMRT/RMRT.h>
#include <RMRT/Objects/HittableList.h>
#include <RMRT/Objects/Sphere.h>
#include <RMRT/Camera/Camera.h>
#include <RMRT/Materials/Material.h>

#include <iostream>

int main()
{
	using namespace rmrt;

	// Image
	constexpr auto aspectRatio{ 16.0 / 9.0 };  // 16:9
	constexpr int imgWidth{ 2160 };
	constexpr int imgHeight{ static_cast<int>(imgWidth / aspectRatio) };
	constexpr int samplesPerPixel{ 100000 };
	constexpr int maxDepth{ 50000 };

	// World
	HittableList world{};

	auto materialGround{ std::make_shared<Lambertian>(colorMap[TempColor::greenish]) };
	auto materialCenter{ std::make_shared<Lambertian>(colorMap[TempColor::pink]) };
	auto materialLeft{ std::make_shared<MetalMaterial>(colorMap[TempColor::bluish]) };
	auto materialRight{ std::make_shared<MetalMaterial>(colorMap[TempColor::goldish]) };

	world.Store(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, materialGround));
	world.Store(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, materialCenter));
	world.Store(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	world.Store(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

	// Camera
	Camera camera{};

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
			Color pixelColor(0, 0, 0);
			for (int k{ 0 }; k < samplesPerPixel; ++k) {
				// 'u' and 'v' are the superimposed axes over the camera viewport axes
				auto u{ (j + RandomDouble()) / cWidth };
				auto v{ (i + RandomDouble()) / cHeight };
				Ray ray{ camera.GetRay(u, v) };
				pixelColor += RayColor(ray, world, maxDepth);
			}
			WriteColor(std::cout, pixelColor, samplesPerPixel);
		}
	}
	// Progress completed
	std::cerr << "\nDone.\n";
}