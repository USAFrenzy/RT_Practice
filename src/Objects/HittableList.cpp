
#include <RMRT/Objects/HittableList.h>
#include <RMRT/RMRT.h>

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

	bool HittableList::Hit(const Ray& ray, double tmin, double tMax, HitRecord& record) const
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

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// This function is used to blend the colors in the background, the author states it's a gradient of blue to white.
	// This is using linear interpolation with the equation: 
	// 
	//                      blendedValue = (1-t)*startValue + (t*endValue)
	// 
	//  NOTE: In the paragraph under this exceprt in module 4.2, the explanation basically tells us that this is dependant on
	//    clamping the Color points between '0' and '1' for the gradient. (when t = 0.0 -> white, when t = 1.0 -> blue) on the 
	//    normalized Y-Axis.
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Color rmrt::HittableList::RayColor(const Ray& ray, const HittableObject& worldObject)
	{
		// From module 5.2, we are hard-coding the sphere center, radius, and color produced when the ray hits the sphere;
		// In actual code, this would most likely be dynamic in the form of input paramaters and attributes instead.
		// Module 6 added a condition on shading the sphere if the ray hits it by normalizing the vector point |_ to the sphere.
		// Module 6.7 added a hit record while normalizing the hits in the direction of the ray as well as the 
		// hittable object paramater to calculate against
		HitRecord record;
		if (worldObject.Hit(ray, 0, infinity, record)) {
			return 0.5 * (record.normal + (colorMap[TempColor::white]));
		}
		Vec3 unitDirection{ UnitVector(ray.Direction()) };
		auto	t = 0.5 * (unitDirection.Y() + 1.0);
		return ((1.0 - t) * colorMap[TempColor::white]) + (t * colorMap[TempColor::blue]);
	}

}