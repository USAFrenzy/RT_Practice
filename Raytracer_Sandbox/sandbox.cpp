
#include <RMRT/Bounds/BVH.h>
#include <RMRT/Camera/Camera.h>
#include <RMRT/Image/Image.h>
#include <RMRT/Materials/Dielectric.h>
#include <RMRT/Materials/Lambertian.h>
#include <RMRT/Materials/Metal.h>
#include <RMRT/Objects/HittableList.h>
#include <RMRT/Objects/Sphere.h>
#include <RMRT/RMRT.h>

#include <chrono>
#include <iostream>

// NOTE TO SELF: In cmake generation, set "/arch:AVX2" since I'm running this on a 10900k desktop and a 10750H laptop CPU

#define TOGGLE_TRUE_SANDBOX 0

int main() {
	using namespace rmrt;

	[[maybe_unused]] std::string_view fileName { "sandbox.ppm" };
	[[maybe_unused]] constexpr auto aspectRatio { 16.0f / 9.0f };    // 16:9
	[[maybe_unused]] constexpr int sdWidth { 480 };                  // 270p
	[[maybe_unused]] constexpr int fsdWidth { 640 };                 // 360p
	[[maybe_unused]] constexpr int hdWidth { 1280 };                 // 720p
	[[maybe_unused]] constexpr int fhdWidth { 1920 };                // 1080p
	[[maybe_unused]] constexpr int qhdWidth { 2560 };                // 1440p
	[[maybe_unused]] constexpr int uhdWidth { 3840 };                // 4k

#if TOGGLE_TRUE_SANDBOX

	// Image
	[[maybe_unused]] constexpr int defaultWidth { 400 };

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Creating the render context; this portion and this class isn't a part of the tutorial
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Image image(fileName, aspectRatio, defaultWidth);

	image.SetDimensions(fsdWidth);
	image.SetRaySampleCount(500);
	image.SetDiffuseRayCount(50);

	// World
	HittableList world {}, worldList {};

	auto materialGround { std::make_shared<LambertianMaterial>(colorMap[ TempColor::greenish ]) };
	auto materialCenter { std::make_shared<LambertianMaterial>(colorMap[ TempColor::pink ]) };
	auto materialLeft { std::make_shared<MetalMaterial>(colorMap[ TempColor::bluish ], 0.8f) };
	auto materialRight { std::make_shared<MetalMaterial>(colorMap[ TempColor::goldish ], 0.25f) };
	auto materialGlass { std::make_shared<DielectricMaterial>(1.52f) };

	world.Store(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, materialGround));
	world.Store(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, materialCenter));
	world.Store(std::make_shared<Sphere>(Point3(-1.1f, 0.0f, -1.0f), 0.5f, materialLeft));
	world.Store(std::make_shared<Sphere>(Point3(1.1f, 0.0f, -1.0f), 0.5f, materialRight));
	world.Store(std::make_shared<Sphere>(Point3(-0.48f, -0.36f, -0.78f), 0.145f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(-0.48f, -0.05f, -0.65f), 0.1f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(0.48f, -0.36f, -0.78f), 0.145f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(0.48f, -0.05f, -0.65f), 0.1f, materialGlass));

	worldList.Store(std::make_shared<BVH_Node>(world, 0.0f, 0.0f));

	// Camera
	auto lookFrom { Point3(0, 0, 1) };
	auto lookAt { Point3(0, 0, -1) };
	auto vertUp { Vec3(0, 1, 0) };
	auto fov { 55.0f };
	auto dof { 1.0f };
	auto aperture { 0.0f };    //  '0.0f'  effectively disables depth of field effect

	Camera camera { lookFrom, lookAt, vertUp, fov, aspectRatio, aperture, dof, 0.0f, 0.0f };

	// Render
	std::cout << "\nRendering Image At: [ " << image.ImageWidth() << "x" << image.ImageHeight() << " ] To File '" << fileName << "'\n"
			  << "Ray Samples Per Pixel : [" << image.RaySampleCount() << " ] "
			  << "Diffuse Rays Per Pixel: [ " << image.DiffuseRayCount() << " ]\n";
	auto begin { std::chrono::steady_clock::now() };
	image.TraceImage(camera, worldList);
	auto end { std::chrono::steady_clock::now() };
	auto elapsed { std::chrono::duration_cast<std::chrono::seconds>(end - begin) };
	std::cout << "\nImage Render Took: [ " << elapsed << " ]\n";
	image.PrintImageToFile();

#else

	// Image
	[[maybe_unused]] constexpr int defaultFinalSceneWidth { 1200 };
	//  fileName = "Final_Scene_1.ppm";
	fileName = "test.ppm";
	// World
	HittableList world {};
	world.Store(std::make_shared<BVH_Node>(std::move(world.RandomScene()), 0.0f, 0.0f));

	// Camera
	Point3 lookFrom { 13.0f, 2.0f, 3.0f };
	Point3 lookAt { 0.0f, 0.0f, 0.0f };
	Vec3 vertUp { 0.0f, 2.0f, 0.0f };
	auto depthOfField { 100.0f };
	auto aperture { 0.05f };
	auto fov { 35.0f };

	Camera cam { lookFrom, lookAt, vertUp, fov, aspectRatio, aperture, depthOfField, 0.0f, 1.0f };

	// Render
	Image image(fileName, aspectRatio, defaultFinalSceneWidth);
	image.SetDimensions(sdWidth);
	image.SetRaySampleCount(500);
	image.SetDiffuseRayCount(50);

	std::cout << "\nRendering Image At: [ " << image.ImageWidth() << "x" << image.ImageHeight() << " ] To File '" << fileName << "'\n"
			  << "Ray Samples Per Pixel : [" << image.RaySampleCount() << " ] "
			  << "Diffuse Rays Per Pixel: [ " << image.DiffuseRayCount() << " ]\n";
	auto begin { std::chrono::steady_clock::now() };
	image.TraceImage(cam, world);
	auto end { std::chrono::steady_clock::now() };
	auto elapsed { std::chrono::duration_cast<std::chrono::seconds>(end - begin) };
	std::cout << "Image Render Took: [ " << elapsed << " ]\n";
	image.PrintImageToFile();
#endif
}