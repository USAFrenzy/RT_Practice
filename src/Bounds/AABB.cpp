
#include <RMRT/Bounds/AABB.h>

namespace rmrt {
	AABB SurroundingBox(AABB box0, AABB box1)
	{
		Point3 small{ fmin(box0.Min().X(), box1.Min().X()),
							   fmin(box0.Min().Y(), box1.Min().Y()) ,
							   fmin(box0.Min().Z(), box1.Min().Z()) };
		Point3 big{ fmax(box0.Max().X(), box1.Max().X()),
							fmax(box0.Max().Y(), box1.Max().Y()) ,
							fmax(box0.Max().Z(), box1.Max().Z()) };
		return AABB(small, big);
	}
}
