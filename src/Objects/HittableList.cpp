
#include <RMRT/Objects/HittableList.h>

namespace rmrt {
	HittableList::HittableList()
	{
	}

	HittableList::HittableList(std::shared_ptr<HittableObject> object)
	{
		Store(object);
	}

	HittableList::~HittableList()
	{
	}

	void HittableList::Clear()
	{
		m_objects.clear();
	}

	void HittableList::Store(std::shared_ptr<HittableObject> object)
	{
		m_objects.emplace_back(std::move(object));
	}

	bool HittableList::Hit(const Ray& ray, float tmin, float tMax, HitRecord& record) const
	{
		HitRecord tempRecord;
		bool isHit{ false };
		auto closestHit{ tMax };

		for (const auto& object : m_objects) {
			if (object->Hit(ray, tmin, closestHit, tempRecord)) {
				isHit = true;
				closestHit = tempRecord.t;
				record = tempRecord;
			}
		}
		return isHit;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// This function is used to blend the colors in the background, the author states it's a gradient of blue to white.
	// This is using linear interpolation with the equation: 
	// 
	//                      blendedValue = (1-t)*startValue + (t*endValue)
	// 
	//  NOTE: In the paragraph under this exceprt in module 4.2, the explanation basically tells us that this is 
	// dependant on clamping the Color points between '0' and '1' for the gradient. (when t = 0.0 -> white, 
	// when t = 1.0 -> blue) on the normalized Y-Axis.
	// 
	// From module 5.2, we are hard-coding the sphere center, radius, and color produced when the ray hits the 
	// sphere; In actual code, this would most likely be dynamic in the form of input paramaters and attributes 
	// instead. 
	// 
	// Module 6 added a condition on shading the sphere if the ray hits it by normalizing 
	// the vector point |_ to the sphere.
	// 
	// Module 6.7 added a hit record while normalizing the hits in the direction of the ray as well as the 
	// hittable object paramater to calculate against
	//
	// Module 8.1 Changes the first if statement to look upon the normal of the surface hit and generate a diffuse ray
	// 
	// 	Module 8.2 Adds a depth parameter to limit how many child rays are produced when recursing and return the
	// 	color black when the limit has been reached.
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Color RayColor(const Ray& ray, const HittableObject& worldObject, int depth)
	{
		HitRecord record;
		if (depth <= 0.0f) return colorMap[TempColor::black];
		if (worldObject.Hit(ray, 0.001f, infinity, record)) {
			Ray scattered;
			Color attenuation;
			if (record.materialPtr->Scatter(ray, record, attenuation, scattered))
			{
				return attenuation * RayColor(scattered, worldObject, --depth);
			}
			Point3 target{ record.p + record.normal + RandomUnitVector() };
			return 0.5f * RayColor(Ray(record.p, target - record.p), worldObject, --depth);
		}
		auto rayDirection {ray.Direction()};
		Vec3 unitDirection{ (rayDirection/rayDirection.Length()) };
		auto	t = 0.5f * (unitDirection.Y() + 1.0f);
		return Lerp(1, colorMap[TempColor::white], colorMap[TempColor::blue] );
	}

}