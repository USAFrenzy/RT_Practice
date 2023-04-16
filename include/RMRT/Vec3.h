#pragma once

#include <ostream>

namespace rmrt {


	class Vec3 {
	public:
		inline constexpr Vec3() :e{ 0,0,0 } {}
		inline constexpr Vec3(float e0, float e1, float e2) : e{ e0, e1, e2 } {}
		inline constexpr void Clear() noexcept {
			e[0] = e[1] = e[2] = 0.0;
		}
		[[nodiscard]] inline constexpr float X() const noexcept {
			return e[0];
		}
		[[nodiscard]] inline constexpr float Y() const noexcept {
			return e[1];
		}
		[[nodiscard]] inline constexpr float Z() const noexcept {
			return e[2];
		}
		[[nodiscard]] float Length() const noexcept;

		[[nodiscard]] inline constexpr float LengthSquared() const noexcept {
			return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
		}

		[[nodiscard]] bool NearZero() const noexcept;
		[[nodiscard]] static Vec3 Random() noexcept;
		[[nodiscard]] static Vec3 Random(float min, float max) noexcept;

		// operator overloads
		[[nodiscard]] inline constexpr Vec3 operator-() const noexcept {
			return Vec3(-e[0], -e[1], -e[2]);
		}
		[[nodiscard]] inline constexpr float operator[](int i) const noexcept {
			return e[i];
		}
		[[nodiscard]] inline constexpr float& operator[](int i) noexcept {
			return e[i];
		}
		inline constexpr Vec3& operator +=(const Vec3& v) noexcept {
			e[0] += v.e[0];
			e[1] += v.e[1];
			e[2] += v.e[2];
			return *this;
		}
		[[nodiscard]] inline constexpr Vec3& operator*=(const float t) noexcept {
			e[0] *= t;
			e[1] *= t;
			e[2] *= t;
			return *this;
		}
		[[nodiscard]] inline constexpr Vec3& operator/=(const float t) noexcept {
			return *this *= 1 / t;
		}

	public:
		float e[3];
	};
	// In my own code, I might make these inherit from or be composed by Vec3 
	// for type safety reasons, but for the tutorial, I'll use them as-is
	using Point3 = Vec3;
	using Color = Vec3;

	// The utility functions for Vec3
	std::ostream& operator<<(std::ostream& out, const Vec3& v) noexcept;
	
	[[nodiscard]] inline constexpr Vec3 operator+(const Vec3& u, const Vec3& v) noexcept 
	{
		return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
	}

	[[nodiscard]] inline constexpr Vec3 operator-(const Vec3& u, const Vec3& v) noexcept
	{
		return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	}

	[[nodiscard]] inline constexpr Vec3 operator*(const Vec3& u, const Vec3& v) noexcept
	{
		return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
	}

	[[nodiscard]] inline constexpr Vec3 operator*(float t, const Vec3& v) noexcept
	{
		return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	[[nodiscard]] inline constexpr Vec3 operator*(int t, const Vec3& v) noexcept
	{
			return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	[[nodiscard]] inline constexpr Vec3 operator*(const Vec3& v, float t) noexcept
	{
		return t * v;
	}

	[[nodiscard]] inline constexpr Vec3 operator/(Vec3 v, float t) noexcept
	{
		return (1 / t) * v;
	}

	[[nodiscard]] inline constexpr float Dot(const Vec3& u, const Vec3& v) noexcept 
	{
		return (u.e[0] * v.e[0]) + (u.e[1] * v.e[1]) + (u.e[2] * v.e[2]);
	}

	/**************************************************************************************************************************
	*  Just like with the other vector concepts, notating this one out for a refresher.
	*
	*  For Cross Products:
	*
	*  1) We create a 3D matrix of each component of the vectors:
	*       i  j  k
	*     | a1  b1  c1  |
	*     | a2  b2  c2  |
	*  2) We then find the determinants by taking each component multiplied by its respective 2D matrix by x-multiplying
	*     (subtracting the second term from the first) each 2D matrix by the corresponding 3D component factor:
	*     (  |  b1  c1  |        )      (  |  a1  c1  |         )     (  |  a1  b1  |  )         )
	*     (  |  b2  c2  |  * i   )   -  (  |  a2  c2  |   *  j  )  +  (  |  a2  b2  |  )   *  k  )   ---->
	*     a  x  b  =  ((( b1*c2)-(c1*b2) )* i) - ((( a1*c2)-(c1*a2) )* j)  + ((( a1*b2)-(b1*a2) )* k)
	*  3) The only difference here, is that instead of the full calculation, we are just creating and returning a Vec3 object with the computed values.
	*************************************************************************************************************************/
	[[nodiscard]] inline constexpr Vec3 Cross(const Vec3& u, const Vec3& v) noexcept
	{
		return Vec3(
			((u.e[1] * v.e[2]) - (u.e[2] * v.e[1])),
			((u.e[2] * v.e[0]) - (u.e[0] * v.e[2])),
			((u.e[0] * v.e[1]) - (u.e[1] * v.e[0]))
		);
	}

	[[nodiscard]] inline constexpr Vec3 UnitVector(Vec3 v) noexcept
	{
		return v / v.Length();
	}

	[[nodiscard]] Vec3 RandomInUnitSphere() noexcept;
	[[nodiscard]] Vec3 RandomInUnitDisc() noexcept;
	[[nodiscard]] Vec3 RandomUnitVector() noexcept;
	
	[[nodiscard]] Vec3 inline constexpr Reflect(const Vec3& v, const Vec3& n) noexcept
	{
		return v - (2 * n * Dot(v, n));
	}

	[[nodiscard]] Vec3 Refract(const Vec3& uv, const Vec3& n, float etai_over_etat) noexcept;
	[[nodiscard]] inline constexpr Color Lerp(float t, const Color& c1, const Color& c2) noexcept
	{
		return (1.0f - t) * c1 + t * c2;
	}
}
