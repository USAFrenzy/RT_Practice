
#include <RMRT/RMRT.h>
#include <RMRT/Vec3.h>

#include <cmath>

namespace rmrt {

	[[nodiscard]] float Vec3::Length() const noexcept {
		return std::sqrt(LengthSquared());
	}

	[[nodiscard]] bool Vec3::NearZero() const noexcept {
		const auto s = 1e-8;
		return (fabs(e[ 0 ]) < s) && (fabs(e[ 1 ]) < s) && (fabs(e[ 2 ]) < s);
	}

	[[nodiscard]] Vec3 Vec3::Random() noexcept {
		return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
	}

	[[nodiscard]] Vec3 Vec3::Random(float min, float max) noexcept {
		return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
	}

	[[nodiscard]] Vec3 RandomInUnitSphere() noexcept {
		for( ;; ) {
				auto p { Vec3::Random(-1, 1) };
				if( p.LengthSquared() < 1.0 ) return p;
				continue;
			}
	}

	[[nodiscard]] Vec3 rmrt::RandomUnitVector() noexcept {
		// The original call called "UnitVector(RandomInUnitSphere())"; I believe just directly looping and dividing into
		// itself instead of producing a new register load and divide would be more efficient as a low-hanging fruit here,
		// however, the extra variable used to store the length squared result might negate that change. At the same time
		// though, it should be a net-benefit since the original loop would have basically called LengthSquared() twice
		// before taking the square root anyways.

		// return UnitVector(RandomInUnitSphere());

		for( ;; ) {
				auto p { Vec3::Random(-1, 1) };
				if( const auto result { p.LengthSquared() }; result < 1.0 ) return p /= std::sqrt(result);
				continue;
			}
	}

	Vec3 rmrt::RandomInUnitDisc() noexcept {
		for( ;; ) {
				auto p { Vec3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0.0f) };
				if( p.LengthSquared() >= 1.0f ) continue;
				return p;
			}
	}

	// The utility functions
	std::ostream& operator<<(std::ostream& out, const Vec3& v) noexcept {
		return out << v.e[ 0 ] << ' ' << v.e[ 1 ] << ' ' << v.e[ 2 ];
	}

	// Takes into consideration Snell's Law ( n*sin0 = n'*sin0' ) where:
	// both 0 & 0' are angles from the normal and both n and n' are the refractive indices
	// 1) To solve for the direction of the refracted ray, solve for sin0'
	//    This leaves us with sin0'=n/n'*sin0 where the refracted rays can be split into their |_ and || counterparts
	//    This now leaves us with two ray functions: A) R' = n/n'(R + cos0*n)   and   B) R'|| = - sqrt(1 - |R'|_ |^2*n)
	// 2) The dot product between two vectors can be simplified as the cosine angle between them to get: a*b = cos0
	// 3) This leaves the final equation as: R'|_ = n/n' * (R + (-R*n)*n)
	[[nodiscard]] Vec3 rmrt::Refract(const Vec3& uv, const Vec3& n, float etai_over_etat) noexcept {
		auto cosineTheta { fmin(Dot(-uv, n), 1.0f) };
		Vec3 perpendicularRayOut { etai_over_etat * (uv + (cosineTheta * n)) };
		Vec3 parallelRayOut { -sqrt(fabs(1.0f - perpendicularRayOut.LengthSquared())) * n };
		return perpendicularRayOut += parallelRayOut;
	}

}    // namespace rmrt
