
#include <RMRT/Bounds/BVH.h>
#include <RMRT/Camera/Camera.h>
#include <RMRT/Image/Image.h>
#include <RMRT/Materials/Dielectric.h>
#include <RMRT/Materials/Lambertian.h>
#include <RMRT/Materials/Metal.h>
#include <RMRT/Objects/HittableList.h>
#include <RMRT/Objects/Sphere.h>
#include <RMRT/RMRT.h>
#include <RMRT/Textures/CheckerTexture.h>

#include <RMRT/Textures/MarbleTexture.h>
#include <RMRT/Textures/NoiseTexture.h>
#include <chrono>
#include <iostream>

#define TOGGLE_TRUE_SANDBOX      0
#define TOGGLE_SCENE_ONE         0
#define TOGGLE_TWO_SPHERES_SCENE 0
#define TOGGLE_EARTH_SCENE       1
#define TOGGLE_SCENE_TWO         0

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
	[[maybe_unused]] constexpr int defaultFinalSceneWidth { 1200 };

#if TOGGLE_TRUE_SANDBOX
	// Image
	[[maybe_unused]] constexpr int defaultWidth { 400 };

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Creating the render context; this portion and this class isn't a part of the tutorial
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Image image(fileName, aspectRatio, defaultWidth);
	image.SetDimensions(uhdWidth);
	image.SetRaySampleCount(1000);
	image.SetDiffuseRayCount(500);

	// World
	HittableList world {};

	auto materialGround { std::make_shared<CheckerTexture>(colorMap[ TempColor::greenish ], colorMap[ TempColor::black ]) };
	auto materialCenter { std::make_shared<MarbleTexture>(5.0f) };
	auto materialLeft { std::make_shared<MetalMaterial>(colorMap[ TempColor::bluish ], 0.8f) };
	auto materialRight { std::make_shared<MetalMaterial>(colorMap[ TempColor::goldish ], 0.15f) };
	auto materialGlass { std::make_shared<DielectricMaterial>(1.52f) };

	world.Store(std::make_shared<Sphere>(Point3(0.0f, -100.5f, -1.0f), 100.0f, std::make_shared<LambertianMaterial>(materialGround)));
	world.Store(std::make_shared<Sphere>(Point3(0.0f, 0.0f, -1.0f), 0.5f, std::make_shared<LambertianMaterial>(materialCenter)));
	world.Store(std::make_shared<Sphere>(Point3(-1.1f, 0.0f, -1.0f), 0.5f, materialLeft));
	world.Store(std::make_shared<Sphere>(Point3(1.1f, 0.0f, -1.0f), 0.5f, materialRight));
	world.Store(std::make_shared<Sphere>(Point3(-0.48f, -0.36f, -0.78f), 0.145f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(-0.48f, -0.05f, -0.65f), 0.1f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(0.48f, -0.36f, -0.78f), 0.145f, materialGlass));
	world.Store(std::make_shared<Sphere>(Point3(0.48f, -0.05f, -0.65f), 0.1f, materialGlass));

	// HittableList worldList {};
	// worldList.Store(std::make_shared<BVH_Node>(world, 0.0f, 0.0f));

	// Camera
	auto lookFrom { Point3(0.0f, 0.0f, 1.0f) };
	auto lookAt { Point3(0.0f, 0.0f, -1.0f) };
	auto vertUp { Vec3(0.0f, 1.0f, 0.0f) };
	auto fov { 55.0f };
	auto dof { 150.0f };
	auto aperture { 0.0f };    //  '0.0f'  effectively disables depth of field effect
	auto time1 { 0.0f }, time2 { 0.0f };

	Camera camera { lookFrom, lookAt, vertUp, fov, aspectRatio, aperture, dof, time1, time2 };

	// Render
	std::cout << "\nRendering Image At: [ " << image.ImageWidth() << "x" << image.ImageHeight() << " ] To File '" << fileName << "'\n"
			  << "Ray Samples Per Pixel : [" << image.RaySampleCount() << " ] "
			  << "Diffuse Rays Per Pixel: [ " << image.DiffuseRayCount() << " ]\n";
	auto begin { std::chrono::steady_clock::now() };
	image.TraceImage(camera, world);
	auto end { std::chrono::steady_clock::now() };
	auto elapsed { std::chrono::duration_cast<std::chrono::seconds>(end - begin) };
	std::cout << "\nImage Render Took: [ " << elapsed << " ]\n";
	image.PrintImageToFile();

#elif TOGGLE_SCENE_ONE

	// Image
	fileName = "Final_Scene_1.ppm";
	Image image(fileName, aspectRatio, defaultFinalSceneWidth);
	image.SetRaySampleCount(500);
	image.SetDiffuseRayCount(50);

	// World
	HittableList world {};
	// Keeping the assignment line just due to the weird issue right now of sky rendering with BVH_Node
	world = world.RandomScene();
	// world.Store(std::make_shared<BVH_Node>(std::move(world.RandomScene()), 0.0f, 0.0f));

	// Camera
	Point3 lookFrom { 13.0f, 2.0f, 3.0f };
	Point3 lookAt { 0.0f, 0.0f, 0.0f };
	Vec3 vertUp { 0.0f, 2.0f, 0.0f };
	auto depthOfField { 100.0f };
	auto aperture { 0.05f };
	auto fov { 35.0f };
	auto time1 { 0.0f }, time2 { 1.0f };
	Camera cam { lookFrom, lookAt, vertUp, fov, aspectRatio, aperture, depthOfField, time1, time2 };

	// Render
	std::cout << "\nRendering Image At: [ " << image.ImageWidth() << "x" << image.ImageHeight() << " ] To File '" << fileName << "'\n"
			  << "Ray Samples Per Pixel : [" << image.RaySampleCount() << " ] "
			  << "Diffuse Rays Per Pixel: [ " << image.DiffuseRayCount() << " ]\n";
	auto begin { std::chrono::steady_clock::now() };
	image.TraceImage(cam, world);
	auto end { std::chrono::steady_clock::now() };
	auto elapsed { std::chrono::duration_cast<std::chrono::seconds>(end - begin) };
	std::cout << "Image Render Took: [ " << elapsed << " ]\n";
	image.PrintImageToFile();

#elif TOGGLE_TWO_SPHERES_SCENE

	// Image
	fileName = "TwoSpheres.ppm";
	Image image(fileName, aspectRatio, defaultFinalSceneWidth);
	image.SetDimensions(sdWidth);
	image.SetRaySampleCount(100);
	image.SetDiffuseRayCount(50);

	// World
	HittableList world {};
	// Keeping the assignment line just due to the weird issue right now of sky rendering with BVH_Node
	world = world.TwoPerlinSpheres();
	// world.Store(std::make_shared<BVH_Node>(world.TwoPerlinSpheres(), 0.0f, 0.0f));

	// Camera
	Point3 lookFrom { 13.0f, 2.0f, 3.0f };
	Point3 lookAt { 0.0f, 0.0f, 0.0f };
	Vec3 vertUp { 0.0f, 2.0f, 0.0f };
	auto depthOfField { 100.0f };
	auto aperture { 0.05f };
	auto fov { 35.0f };
	auto time1 { 0.0f }, time2 { 1.0f };
	Camera cam { lookFrom, lookAt, vertUp, fov, aspectRatio, aperture, depthOfField, time1, time2 };

	// Render
	std::cout << "\nRendering Image At: [ " << image.ImageWidth() << "x" << image.ImageHeight() << " ] To File '" << fileName << "'\n"
			  << "Ray Samples Per Pixel : [" << image.RaySampleCount() << " ] "
			  << "Diffuse Rays Per Pixel: [ " << image.DiffuseRayCount() << " ]\n";
	auto begin { std::chrono::steady_clock::now() };
	image.TraceImage(cam, world);
	auto end { std::chrono::steady_clock::now() };
	auto elapsed { std::chrono::duration_cast<std::chrono::seconds>(end - begin) };
	std::cout << "Image Render Took: [ " << elapsed << " ]\n";
	image.PrintImageToFile();

#elif TOGGLE_EARTH_SCENE

	// TODO: Figure out why the image texture isn't mapping correctly to the sphere...

	// Image
	fileName = "EarthScene.ppm";
	Image image(fileName, aspectRatio, defaultFinalSceneWidth);
	image.SetDimensions(400);
	image.SetRaySampleCount(100);
	image.SetDiffuseRayCount(50);

	// World
	HittableList world {};
	// Keeping the assignment line just due to the weird issue right now of sky rendering with BVH_Node
	world = world.Earth();
	// world.Store(std::make_shared<BVH_Node>(world.Earth(), 0.0f, 0.0f));

	// Camera
	Point3 lookFrom { 0.0f, 0.0f, 12.0f };
	Point3 lookAt { 0.0f, 0.0f, 0.0f };
	Vec3 vertUp { 0.0f, 1.0f, 0.0f };
	auto depthOfField { 10.0f };
	auto aperture { 0.0f };
	auto fov { 20.0f };
	auto time1 { 0.0f }, time2 { 1.0f };
	Camera cam { lookFrom, lookAt, vertUp, fov, aspectRatio, aperture, depthOfField, time1, time2 };

	// Render
	std::cout << "\nRendering Image At: [ " << image.ImageWidth() << "x" << image.ImageHeight() << " ] To File '" << fileName << "'\n"
			  << "Ray Samples Per Pixel : [" << image.RaySampleCount() << " ] "
			  << "Diffuse Rays Per Pixel: [ " << image.DiffuseRayCount() << " ]\n";
	auto begin { std::chrono::steady_clock::now() };
	image.TraceImage(cam, world);
	auto end { std::chrono::steady_clock::now() };
	auto elapsed { std::chrono::duration_cast<std::chrono::seconds>(end - begin) };
	std::cout << "Image Render Took: [ " << elapsed << " ]\n";
	image.PrintImageToFile();

#elif TOGGLE_SCENE_TWO

#endif
}