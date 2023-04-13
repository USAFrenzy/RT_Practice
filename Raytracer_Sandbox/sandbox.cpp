
#include <RMRT/RMRT.h>
#include <RMRT/Objects/HittableList.h>
#include <RMRT/Objects/Sphere.h>
#include <RMRT/Camera/Camera.h>
#include <RMRT/Materials/Lambertian.h>
#include <RMRT/Materials/Metal.h>
#include <RMRT/Materials/Dielectric.h>
#include <RMRT/Image/Image.h>

#include <iostream>
#include <chrono>

// NOTE TO SELF: In cmake generation, set "/arch:AVX2" since I'm running this on a 10900k desktop and a 10750H laptop cpu

int main()
{
	using namespace rmrt;

	// Image
	constexpr auto aspectRatio{ 16.0f / 9.0f };  // 16:9
	constexpr int defaultWidth{ 400 };
	constexpr int sdWidth{ 480}; // 270p
	constexpr int fsdWidth{ 640}; // 360p
	constexpr int hdWidth{ 1280 }; // 720p
	constexpr int fhdWidth{ 1920 }; // 1080p
	constexpr int qhdWidth{ 2560 }; // 1440p
	constexpr int uhdWidth{ 3840 }; // 4k

	constexpr std::string_view fileName {"default.ppm"};

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Creating the render context; this portion and this class isn't a part of the tutorial
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// uses default RTIOW settings, this is here if the below lines regarding the image 
	// context are commented out so as to keep to the original image render
	Image image(fileName, aspectRatio, defaultWidth); 
	
	//image.SetDimensions(qhdWidth);
	//image.SetRaySampleCount(10'000);
	//image.SetDiffuseRayCount(1250);

	// World
	HittableList world{};

	auto materialGround{ std::make_shared<LambertianMaterial>(colorMap[TempColor::greenish]) };
	auto materialCenter{ std::make_shared<LambertianMaterial>(colorMap[TempColor::pink]) };
	auto materialLeft{ std::make_shared<MetalMaterial>(colorMap[TempColor::bluish], 0.8f) };
	auto materialRight{ std::make_shared<MetalMaterial>(colorMap[TempColor::goldish], 0.25f) };
	auto materialGlass{ std::make_shared<DielectricMaterial>(1.52f) };

	world.Store(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
	world.Store(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, materialCenter));
	world.Store(std::make_shared<Sphere>(Point3(-1.1f, 0.0f, -1.0f), 0.5f, materialLeft));
	world.Store(std::make_shared<Sphere>(Point3(1.1f, 0.0f, -1.0f), 0.5f, materialRight));
	world.Store(std::make_shared<Sphere>(Point3(-0.48f, -0.38f, -0.78f), 0.145f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(-0.48f, -0.12f, -0.65f), 0.1f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(0.48f, -0.38f, -0.78f), 0.145f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(0.48f, -0.12f, -0.65f), 0.1f, materialGlass));



	// Camera
	auto lookFrom { Point3(0, 0, 1) };
	auto lookAt{ Point3(0, 0, -1) };
	auto vertUp {Vec3(0, 1, 0)};
	auto fov {60.0f};

	Camera camera{lookFrom, lookAt, vertUp, fov, aspectRatio};

	// Render
	std::cout << "\nRendering Image At: [ " << image.ImageWidth() << "x" << image.ImageHeight() << " ] To File '" << fileName <<"'\n" 
		<< "Ray Samples Per Pixel : [" << image.RaySampleCount() << " ] " << "Diffuse Rays Per Pixel: [ " << image.DiffuseRayCount() << " ]\n";
	auto begin {std::chrono::steady_clock::now()};
	image.TraceImage(camera, world);
	auto end { std::chrono::steady_clock::now() };
	auto elapsed {std::chrono::duration_cast<std::chrono::seconds>(end-begin)};
	std::cout << "\nImage Render Took: [ " << elapsed << " ]\n";

}