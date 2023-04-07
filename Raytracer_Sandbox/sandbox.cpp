
#include <RMRT/RMRT.h>
#include <RMRT/Objects/HittableList.h>
#include <RMRT/Objects/Sphere.h>
#include <RMRT/Camera/Camera.h>
#include <RMRT/Materials/Material.h>
#include <RMRT/Materials/Metal.h>
#include <RMRT/Image/Image.h>

#include <iostream>

int main()
{
	using namespace rmrt;

	// Image
	constexpr auto aspectRatio{ 16.0 / 9.0 };  // 16:9
	constexpr int defaultWidth{ 400 };
	constexpr int hdWidth{ 1920 };
	constexpr int qhdWidth{ 2560 };
	constexpr int uhdWidth{ 3840 };

	Image image("image.ppm", aspectRatio, qhdWidth); // uses default RTIOW settings
	image.SetDimensions(qhdWidth);
	image.SetRaySampleCount(10000);
	image.SetDiffuseRayCount(1000);

	// World
	HittableList world{};

	auto materialGround{ std::make_shared<Lambertian>(colorMap[TempColor::greenish]) };
	auto materialCenter{ std::make_shared<Lambertian>(colorMap[TempColor::pink]) };
	auto materialLeft{ std::make_shared<MetalMaterial>(colorMap[TempColor::bluish], 0.2) };
	auto materialRight{ std::make_shared<MetalMaterial>(colorMap[TempColor::goldish], 1.0) };

	world.Store(std::make_shared<Sphere>(Point3(0, -100.5, -1), 100, materialGround));
	world.Store(std::make_shared<Sphere>(Point3(0, 0, -1), 0.5, materialCenter));
	world.Store(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
	world.Store(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

	// Camera
	Camera camera{};
	camera.SetFocalLength(1.25);

	// Render
	image.TraceImage(camera, world);

}