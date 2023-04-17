#pragma once

#include <RMRT/Ray.h>
#include <RMRT/Objects/HittableObject.h>
#include <RMRT/Objects/HittableList.h>


namespace rmrt {

	class BVH_Node : public HittableObject
	{
	public:
		BVH_Node();
		BVH_Node(const HittableList& list, float time0, float time1);
		BVH_Node(const HittableList::HittableObjectList& srcObjects, size_t start, size_t end, float time0, float time1);

		inline constexpr virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const
		{
			if (!m_box.Hit(ray, tMin, tMax)) return false;
			bool leftHit{ m_left->Hit(ray, tMin, tMax, record) };
			bool rightHit{ m_right->Hit(ray, tMin, leftHit ? record.t : tMax, record) };
			return leftHit || rightHit;
		}

		inline constexpr virtual bool BoundingBox(float time0, float time1, AABB& outputBox) const override
		{
			outputBox = m_box;
			return true;
		}

	private:
		std::shared_ptr<HittableObject> m_left;
		std::shared_ptr<HittableObject> m_right;
		AABB m_box;
	};

	inline bool BoxCompare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b, int axis)
	{
		AABB boxA;
		AABB boxB;

		if (!a->BoundingBox(0.0f, 0.0f, boxA) || !b->BoundingBox(0.0f, 0.0f, boxB)) {
			fprintf(stderr, "No Bounding Box In BVH_Node Constructor.\n");
		}
		return boxA.Min().e[axis] < boxB.Min().e[axis];
	}
	bool BoxXCompare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b);
	bool BoxYCompare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b);
	bool BoxZCompare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b);
}
