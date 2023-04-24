
#include <RMRT/Noise/Perlin.h>

namespace rmrt {

	PerlinNoise::PerlinNoise()
		: m_pointCount(256), m_randVec(new Vec3[ m_pointCount ]), m_permX(PerlinPermutation()), m_permY(PerlinPermutation()), m_permZ(PerlinPermutation()) {
		for( int i { 0 }; i < m_pointCount; ++i ) {
				m_randVec[ i ] = UnitVector(Vec3::Random(-1.0f, 1.0f));
			}
	}

	PerlinNoise::~PerlinNoise() {
		delete[] m_randVec;
		delete[] m_permX;
		delete[] m_permY;
		delete[] m_permZ;
	}

	float PerlinNoise::Noise(const Point3& p) const {
		auto u { p.X() - floor(p.X()) };
		auto v { p.Y() - floor(p.Y()) };
		auto w { p.Z() - floor(p.Z()) };

		// Hermitian Smoothing
		u = u * u * (3 - 2 * u);
		v = v * v * (3 - 2 * v);
		w = w * w * (3 - 2 * w);

		auto i { static_cast<int>(floor(p.X())) };
		auto j { static_cast<int>(floor(p.Y())) };
		auto k { static_cast<int>(floor(p.Z())) };
		Vec3 c[ 2 ][ 2 ][ 2 ];
		// Hashing the perlin noise generated
		for( int di { 0 }; di < 2; di++ ) {
				for( int dj { 0 }; dj < 2; dj++ ) {
						for( int dk { 0 }; dk < 2; dk++ ) {
								c[ di ][ dj ][ dk ] = m_randVec[ m_permX[ (i + di) & 255 ] ^ m_permY[ (j + dj) & 255 ] ^ m_permZ[ (k + dk) & 255 ] ];
							}
					}
			}
		// Smoothing out the perlin noise generated
		return PerlinInterpolate(c, u, v, w);
	}

	int* PerlinNoise::PerlinPermutation() {
		auto p = new int[ m_pointCount ];
		for( int i = 0; i < PerlinNoise::m_pointCount; i++ ) p[ i ] = i;
		Permutate(p, m_pointCount);
		return p;
	}

	void PerlinNoise::Permutate(int* p, int n) {
		for( int i = n - 1; i > 0; i-- ) {
				int target  = RandomInt(0, i);
				int tmp     = p[ i ];
				p[ i ]      = p[ target ];
				p[ target ] = tmp;
			}
	}

	float rmrt::PerlinNoise::TrilinearInterpolate(float c[ 2 ][ 2 ][ 2 ], float u, float v, float w) const {
		auto accumulate { 0.0f };
		for( int i { 0 }; i < 2; i++ ) {
				for( int j { 0 }; j < 2; j++ ) {
						for( int k { 0 }; k < 2; k++ ) {
								// clang-format off
								accumulate += 
									(i * u + (1 - i) * (1 - u)) 
									* (j * v + (1 - j) * (1 - v))
									* (k * w + (1 - k) * (1 - w)) 
									* c[ i ][ j ][ k ];
								// clang-format off
							}
					}
			}
		return accumulate;
	}

	float PerlinNoise::PerlinInterpolate(Vec3 c[ 2 ][ 2 ][ 2 ], float u, float v, float w) const {
		auto uu { u * u * (3 - 2 * u) };
		auto vv { v * v * (3 - 2 * v) };
		auto ww { w * w * (3 - 2 * w) };
		auto accumulate { 0.0f };
		for( int i { 0 }; i < 2; i++ ) {
				for( int j { 0 }; j < 2; j++ ) {
						for( int k { 0 }; k < 2; k++ ) {
								Vec3 weight_v { u - i, v - j, w - k };
								// clang-format off
								accumulate += 
									(i * uu + (1 - i) * (1 - uu)) 
									* (j * vv + (1 - j) * (1 - vv)) 
									* (k * ww + (1 - k) * (1 - ww)) 
									*  Dot(c[ i ][ j ][ k ], weight_v);
								// clang-format on
							}
					}
			}
		return accumulate;
	}

	float PerlinNoise::Turbulence(const Point3& p, int depth) const {
		auto accumulate { 0.0f };
		auto tempP { p };    // makes local copy to modify below
		auto weight { 1.0f };
		for( int i { 0 }; i < depth; i++ ) {
				accumulate += weight * Noise(tempP);
				weight *= 0.5;
				tempP *= 2;
			}
		return fabs(accumulate);
	}

}    // namespace rmrt
