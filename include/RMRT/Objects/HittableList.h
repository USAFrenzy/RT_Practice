#pragma once

#include <RMRT/RMRT.h>
#include <RMRT/Objects/HittableObject.h>

#include <vector>
#include <RMRT/Ray.h>

namespace rmrt {

	class HittableList : public HittableObject
	{
	public:
		using HittableObjectList = std::vector<std::shared_ptr<HittableObject>>;

		HittableList();
		HittableList(std::shared_ptr<HittableObject> object);
		~HittableList();

		void Clear();
		void Store(std::shared_ptr<HittableObject> object);
		virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const override;
		virtual bool BoundingBox(float time0, float time1, AABB& outputBox) const override;
		inline const HittableObjectList& Objects() const { return m_objects; }
		HittableList RandomScene();

	private:
		HittableObjectList m_objects;
	};
		Color RayColor(const Ray& ray, const HittableObject& worldObject, int depth);
}