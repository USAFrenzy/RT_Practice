
#include <RMRT/Bounds/AABB.h>

namespace rmrt {
	AABB SurroundingBox(AABB box0, AABB box1) {
		Point3 small { std::fmin(box0.Min().X(), box1.Min().X()), std::fmin(box0.Min().Y(), box1.Min().Y()), std::fmin(box0.Min().Z(), box1.Min().Z()) };
		Point3 big { std::fmax(box0.Max().X(), box1.Max().X()), std::fmax(box0.Max().Y(), box1.Max().Y()), std::fmax(box0.Max().Z(), box1.Max().Z()) };
		return AABB(small, big);
	}
}    // namespace rmrt
