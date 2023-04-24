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
		float TrilinearInterpolate(float c[ 2 ][ 2 ][ 2 ], float u, float v, float w) const;
		float PerlinInterpolate(Vec3 c[ 2 ][ 2 ][ 2 ], float u, float v, float w) const;
		float Turbulence(const Point3& p, int depth = 7) const;

	  private:
		void Permutate(int* p, int n);
		int* PerlinPermutation();

	  private:
		const int m_pointCount;
		Vec3* m_randVec;
		int* m_permX;
		int* m_permY;
		int* m_permZ;
	};

}    // namespace rmrt
