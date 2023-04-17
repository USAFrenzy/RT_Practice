#pragma once

#include <RMRT/RMRT.h>
#include <RMRT/Materials/Material.h>
#include <RMRT/Bounds/AABB.h>

#include <memory>

namespace rmrt {

	class Material;

	struct HitRecord
	{
		Point3 p {0.0f ,0.0f ,0.0f};
		Vec3 normal {0.0f, 0.0f, 0.0f};
		std::shared_ptr<Material> materialPtr {nullptr};
		float t {0.0f};
		bool frontFace {false};
		Color emissiveColor { colorMap[TempColor::black]};

		// This function simply compares whether or not the vector in question points with or against the ray direction and
		// stores the relative information for the face of the object, whether it's a front facing ray hit or not and if it's not, 
		// stores the vector as a normal with the opposite direction of the ray.
		inline constexpr void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal) {
			frontFace = Dot(ray.Direction(), outwardNormal) < 0;
			normal = frontFace ? outwardNormal : -outwardNormal;
		}
	};

	class HittableObject
	{
	public:
		virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& record) const = 0;
		virtual bool BoundingBox(float time0, float time1, AABB& outputBox) const = 0;
	};
}