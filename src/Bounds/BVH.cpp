
#include <RMRT/Bounds/BVH.h>
#include <algorithm>

namespace rmrt {
	BVH_Node::BVH_Node() { }

	BVH_Node::BVH_Node(const HittableList& list, float time0, float time1): BVH_Node(list.Objects(), 0, list.Objects().size(), time0, time1) { }

	BVH_Node::BVH_Node(const HittableList::HittableObjectList& srcObjects, size_t start, size_t end, float time0, float time1) {
		auto objects { srcObjects };

		int axis { RandomInt(0, 2) };
		auto comparator = (axis == 0) ? BoxXCompare : (axis == 1) ? BoxYCompare : BoxZCompare;

		switch( size_t objectSpan { end - start }; objectSpan ) {
				default:
					{
						std::sort(objects.begin() + start, objects.begin() + end, comparator);
						auto mid { start + objectSpan / 2 };
						m_left  = std::make_shared<BVH_Node>(objects, start, mid, time0, time1);
						m_right = std::make_shared<BVH_Node>(objects, mid, end, time0, time1);
						break;
					}
				case 1:
					{
						m_left = m_right = objects[ start ];
						break;
					}
				case 2:
					{
						if( comparator(objects[ start ], objects[ start + 1 ]) ) {
								m_left  = objects[ start ];
								m_right = objects[ start + 1 ];
						} else {
								m_left  = objects[ start + 1 ];
								m_right = objects[ start ];
							}
						break;
					}
			}
		AABB leftBox, rightBox;
		if( !m_left->BoundingBox(time0, time1, leftBox) || !m_right->BoundingBox(time0, time1, rightBox) ) {
				fprintf(stderr, "No Bounding Box In BVH_Node Constructor.\n");
		}
		m_box = SurroundingBox(leftBox, rightBox);
	}

	bool BoxXCompare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b) {
		return BoxCompare(a, b, 0);
	}

	bool BoxYCompare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b) {
		return BoxCompare(a, b, 1);
	}

	bool BoxZCompare(const std::shared_ptr<HittableObject> a, const std::shared_ptr<HittableObject> b) {
		return BoxCompare(a, b, 2);
	}

}    // namespace rmrt
