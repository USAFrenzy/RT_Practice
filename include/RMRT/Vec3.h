#pragma once

#include <ostream>

namespace rmrt {


	class Vec3 {
	public:
		Vec3() :e{ 0,0,0 } {}
		Vec3(float e0, float e1, float e2) :e{ e0, e1, e2 } {}
		float X() const;
		float Y() const;
		float Z() const;
		float Length() const;
		float LengthSquared() const;
		bool NearZero() const;
		void Clear();
		static Vec3 Random();
		static Vec3 Random(float min, float max);

		// operator overloads
		Vec3 operator-() const;
		float operator[](int i) const;
		float& operator[](int i);
		Vec3& operator +=(const Vec3& v);
		Vec3& operator*=(const float t);
		Vec3& operator/=(const float t);

	public:
		float e[3];
	};
	// In my own code, I might make these inherit from or be composed by Vec3 
	// for type safety reasons, but for the tutorial, I'll use them as-is
	using Point3 = Vec3;
	using Color = Vec3;

	// The utility functions for Vec3
	std::ostream& operator<<(std::ostream& out, const Vec3& v);
	Vec3 operator+(const Vec3& u, const Vec3& v);
	Vec3 operator-(const Vec3& u, const Vec3& v);
	Vec3 operator*(const Vec3& u, const Vec3& v);
	Vec3 operator*(float t, const Vec3& v);
	Vec3 operator*(const Vec3& v, float t);
	Vec3 operator/(Vec3 v, float t);

	float Dot(const Vec3& u, const Vec3& v);
	Vec3 Cross(const Vec3& u, const Vec3& v);
	Vec3 UnitVector(Vec3 v);
	Vec3 RandomInUnitSphere();
	Vec3 RandomUnitVector();
	Vec3 Reflect(const Vec3& v, const Vec3& n);
	Vec3 Refract(const Vec3& uv, const Vec3& n, float etai_over_etat);
}
