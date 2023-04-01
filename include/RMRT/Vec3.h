#pragma once

#include <ostream>

namespace rmrt {

	constexpr auto rgb_factor{ 255.999 };

	class Vec3 {
	public:
		Vec3() :e{ 0,0,0 } {}
		Vec3(double e0, double e1, double e2) :e{ e0, e1, e2 } {}
		double X() const;
		double Y() const;
		double Z() const;
		double Length() const;
		double LengthSquared() const;

		// operator overloads
		Vec3 operator-() const;
		double operator[](int i) const;
		double& operator[](int i);
		Vec3& operator +=(const Vec3& v);
		Vec3& operator*=(const double t);
		Vec3& operator/=(const double t);


	public:
		double e[3];
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
	Vec3 operator*(double t, const Vec3& v);
	Vec3 operator*(const Vec3& v, double t);
	Vec3 operator/(Vec3 v, double t);

	// Scalar
	double Dot(const Vec3& u, const Vec3& v);

	Vec3 Cross(const Vec3& u, const Vec3& v);
	Vec3 UnitVector(Vec3 v);

	void WriteColor(std::ostream& out, Color pixelColor);
}