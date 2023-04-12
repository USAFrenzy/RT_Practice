#pragma once

#include <ostream>

namespace rmrt {


	class Vec3 {
	public:
		Vec3() :e{ 0,0,0 } {}
		Vec3(float e0, float e1, float e2) :e{ e0, e1, e2 } {}
		void Clear() noexcept;
		[[nodiscard]] float X() const noexcept;
		[[nodiscard]] float Y() const noexcept;
		[[nodiscard]] float Z() const noexcept;
		[[nodiscard]] float Length() const noexcept;
		[[nodiscard]] float LengthSquared() const noexcept;
		[[nodiscard]] bool NearZero() const noexcept;
		[[nodiscard]] static Vec3 Random() noexcept;
		[[nodiscard]] static Vec3 Random(float min, float max) noexcept;

		// operator overloads
		[[nodiscard]] Vec3 operator-() const noexcept;
		[[nodiscard]] float operator[](int i) const noexcept;
		[[nodiscard]] float& operator[](int i) noexcept;
		Vec3& operator +=(const Vec3& v)noexcept;
		[[nodiscard]] Vec3& operator*=(const float t)noexcept;
		[[nodiscard]] Vec3& operator/=(const float t)noexcept;

	public:
		float e[3];
	};
	// In my own code, I might make these inherit from or be composed by Vec3 
	// for type safety reasons, but for the tutorial, I'll use them as-is
	using Point3 = Vec3;
	using Color = Vec3;

	// The utility functions for Vec3
	std::ostream& operator<<(std::ostream& out, const Vec3& v)noexcept;
	[[nodiscard]] Vec3 operator+(const Vec3& u, const Vec3& v) noexcept;
	[[nodiscard]] Vec3 operator-(const Vec3& u, const Vec3& v) noexcept;
	[[nodiscard]] Vec3 operator*(const Vec3& u, const Vec3& v) noexcept;
	[[nodiscard]] Vec3 operator*(float t, const Vec3& v) noexcept;
	[[nodiscard]] Vec3 operator*(int t, const Vec3& v) noexcept;
	[[nodiscard]] Vec3 operator*(const Vec3& v, float t) noexcept;
	[[nodiscard]] Vec3 operator/(Vec3 v, float t) noexcept;

	[[nodiscard]] float Dot(const Vec3& u, const Vec3& v) noexcept;
	[[nodiscard]] Vec3 Cross(const Vec3& u, const Vec3& v) noexcept;
	[[nodiscard]] Vec3 UnitVector(Vec3 v) noexcept;
	[[nodiscard]] Vec3 RandomInUnitSphere() noexcept;
	[[nodiscard]] Vec3 RandomUnitVector() noexcept;
	[[nodiscard]] Vec3 Reflect(const Vec3& v, const Vec3& n) noexcept;
	[[nodiscard]] Vec3 Refract(const Vec3& uv, const Vec3& n, float etai_over_etat) noexcept;
	[[nodiscard]] Color Lerp(int t, const Color& c1, const Color& c2) noexcept;
}
