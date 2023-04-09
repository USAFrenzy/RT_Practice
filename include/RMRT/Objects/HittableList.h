#pragma once

#include <RMRT/Objects/HittableObject.h>

#include <vector>

namespace rmrt {

	class HittableList :public HittableObject
	{
	public:
		using HittableObjectList = std::vector<std::shared_ptr<HittableObject>>;

		HittableList();
		HittableList(std::shared_ptr<HittableObject> object);
		~HittableList();

		void Clear();
		void Store(std::shared_ptr<HittableObject> object);
		virtual bool Hit(const Ray& ray, float tmin, float tMax, HitRecord& record) const;

	private:
		HittableObjectList m_objects;
	};
		Color RayColor(const Ray& ray, const HittableObject& worldObject, int depth);
}