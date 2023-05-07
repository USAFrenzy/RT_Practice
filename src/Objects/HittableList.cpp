
#include <RMRT/Materials/Dielectric.h>
#include <RMRT/Materials/Lambertian.h>
#include <RMRT/Materials/Metal.h>
#include <RMRT/Objects/HittableList.h>
#include <RMRT/Objects/Sphere.h>
#include <RMRT/Textures/CheckerTexture.h>
#include <RMRT/Textures/ImageTexture.h>
#include <RMRT/Textures/MarbleTexture.h>
#include <RMRT/Textures/NoiseTexture.h>

namespace rmrt {
	HittableList::HittableList() { }

	HittableList::HittableList(std::shared_ptr<HittableObject> object) {
		Store(object);
	}

	HittableList::~HittableList() { }

	void HittableList::Clear() {
		m_objects.clear();
	}

	void HittableList::Store(std::shared_ptr<HittableObject> object) {
		m_objects.emplace_back(std::move(object));
	}

	bool HittableList::Hit(const Ray& ray, float tmin, float tMax, HitRecord& record) const {
		HitRecord tempRecord;
		bool isHit { false };
		auto closestHit { tMax };

		for( const auto& object: m_objects ) {
				if( object->Hit(ray, tmin, closestHit, tempRecord) ) {
						isHit      = true;
						closestHit = tempRecord.t;
						record     = tempRecord;
				}
			}
		return isHit;
	}

	bool HittableList::BoundingBox(float time0, float time1, AABB& outputBox) const {
		
		if( m_objects.empty() ) return false;
		
		AABB temp;
		bool firstBox { true };
		for( const auto& object: m_objects ) {
				if( !object->BoundingBox(time0, time1, temp) ) return false;
				outputBox = firstBox ? temp : SurroundingBox(outputBox, temp);
				firstBox  = false;
			}
		return true;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// This function is used to blend the colors in the background, the author states it's a gradient of blue to white.
	// This is using linear interpolation with the equation:
	//
	//                      blendedValue = (1-t)*startValue + (t*endValue)
	//
	//  NOTE: In the paragraph under this excerpt in module 4.2, the explanation basically tells us that this is
	// dependent on clamping the Color points between '0' and '1' for the gradient. (when t = 0.0 -> white,
	// when t = 1.0 -> blue) on the normalized Y-Axis.
	//
	// From module 5.2, we are hard-coding the sphere center, radius, and color produced when the ray hits the
	// sphere; In actual code, this would most likely be dynamic in the form of input parameters and attributes
	// instead.
	//
	// Module 6 added a condition on shading the sphere if the ray hits it by normalizing
	// the vector point |_ to the sphere.
	//
	// Module 6.7 added a hit record while normalizing the hits in the direction of the ray as well as the
	// hittable object parameter to calculate against
	//
	// Module 8.1 Changes the first if statement to look upon the normal of the surface hit and generate a diffuse ray
	//
	// 	Module 8.2 Adds a depth parameter to limit how many child rays are produced when recursing and return the
	// 	color black when the limit has been reached.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Color RayColor(const Ray& ray, const HittableObject& worldObject, int depth) {
		HitRecord record;
		if( depth <= 0.0f ) return colorMap[ TempColor::black ];
		if( worldObject.Hit(ray, 0.001f, infinity, record) ) {
				Ray scattered;
				Color attenuation;
				if( record.materialPtr->Scatter(ray, record, attenuation, scattered) ) {
						return attenuation * RayColor(scattered, worldObject, --depth);
				}
				Point3 target { record.p + record.normal + RandomUnitVector() };
				return 0.5f * RayColor(Ray(record.p, target - record.p), worldObject, --depth);
		}
		const auto& rayDirection { ray.Direction() };
		Vec3 unitDirection { (rayDirection / rayDirection.Length()) };
		auto t = 0.5f * (unitDirection.Y() + 1.0f);
		return Lerp(t, colorMap[ TempColor::white ], colorMap[ TempColor::blue ]);
	}

	HittableList rmrt::HittableList::RandomScene() {
		Point3 staticPoint { 4.0f, 0.2f, 0.0f };    // moving this out of the loop
		HittableList world;

		auto groundMaterial { std::make_shared<CheckerTexture>(colorMap[ TempColor::greenish ], colorMap[ TempColor::black ]) };
		world.Store(std::make_shared<Sphere>(Point3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_shared<LambertianMaterial>(groundMaterial)));

		for( int a { -11 }; a < 11; ++a ) {
				for( int b { -11 }; b < 11; ++b ) {
						auto chooseMaterial { RandomDouble() };
						Point3 center { a + (0.9f * RandomDouble()), 0.2f, b + (0.9f * RandomDouble()) };
						if( (center - staticPoint).Length() > 0.9f ) {
								std::shared_ptr<Material> sphereMaterial;
								if( chooseMaterial < 0.55f ) {
										// Diffuse
										auto albedo { Color::Random() * Color::Random() };
										sphereMaterial = std::make_shared<LambertianMaterial>(albedo);
										if( chooseMaterial > 0.2f ) {
												// Stationary Sphere
												world.Store(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
										} else {
												// Moving Sphere
												auto center2 { center + Vec3(0.0f, RandomDouble(0.0f, 0.5f), 0.0f) };
												world.Store(std::make_shared<MovingSphere>(center, center2, 0.0f, 1.0f, 0.2f, sphereMaterial));
											}
								} else if( chooseMaterial < 0.85f ) {
										// Metal
										auto albedo { Color::Random(0.5f, 1.0f) };
										auto fuzzFactor { RandomDouble(0.0f, 0.5f) };
										sphereMaterial = std::make_shared<MetalMaterial>(albedo, fuzzFactor);
										world.Store(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
								} else {
										// Glass
										sphereMaterial = std::make_shared<DielectricMaterial>(1.52f);
										world.Store(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
									}
						}
					}
			}
		auto material1 { std::make_shared<DielectricMaterial>(1.52f) };
		auto material2 { std::make_shared<LambertianMaterial>(Color(0.4f, 0.2f, 0.1f)) };
		auto material3 { std::make_shared<MetalMaterial>(Color(0.7f, 0.6f, 0.5f), 0.0f) };

		world.Store(std::make_shared<Sphere>(Point3(0.0f, 1.0f, 0.0f), 1.0f, material1));
		world.Store(std::make_shared<Sphere>(Point3(-4.0f, 1.0f, 0.0f), 1.0f, material2));
		world.Store(std::make_shared<Sphere>(Point3(4.0f, 1.0f, 0.0f), 1.0f, material3));

		return world;
	}

	HittableList HittableList::TwoPerlinSpheres() {
		HittableList objects;
		auto turbulentTexture { std::make_shared<TurbulentTexture>(4.0f) };
		auto marbleTexture { std::make_shared<MarbleTexture>(4.0f) };
		objects.Store(std::make_shared<Sphere>(Point3(0.0f, -1000.0f, 0.0f), 1000.0f, std::make_shared<LambertianMaterial>(turbulentTexture)));
		objects.Store(std::make_shared<Sphere>(Point3(0.0f, 2.0f, 0.0f), 2.0f, std::make_shared<LambertianMaterial>(marbleTexture)));
		return objects;
	}

	HittableList rmrt::HittableList::Earth() {
		auto earthTexture { std::make_shared<ImageTexture>("Resources/earthmap1.jpg") };
		auto earthSurface { std::make_shared<LambertianMaterial>(earthTexture) };
		auto globe { std::make_shared<Sphere>(Point3(0.0f, 0.0f, 0.0f), 2.0f, earthSurface) };
		return HittableList(globe);
	}

}    // namespace rmrt