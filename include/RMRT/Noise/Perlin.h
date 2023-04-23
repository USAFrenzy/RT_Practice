#pragma once

#include <RMRT/RMRT.h>
#include <RMRT/Vec3.h>

namespace rmrt {

	class PerlinNoise
	{
	  public:
		PerlinNoise();
		~PerlinNoise();
		float Noise(const Point3& p) const;

	  private:
		void Permutate(int* p, int n);
		int* PerlinPermutation();
		float TrilinearInterpolate(float c[2][2][2], float u, float v, float w) const;

	  private:
		const int m_pointCount;
		float* m_randFloat;
		int* m_permX;
		int* m_permY;
		int* m_permZ;
	};

}    // namespace rmrt
