
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

	bool HittableList::Hit(const Ray& ray, double tmin, double tMax, HitRecord& record) const
	{
		HitRecord tempRecord;
		bool isHit {false};
		auto closestHit {tMax};

		for (const auto& object : m_objects) {
			if (object->Hit(ray, tmin, closestHit, tempRecord)) {
				isHit = true;
				closestHit = tempRecord.t;
				record = tempRecord;
			}
		}
		return isHit;
	}

}