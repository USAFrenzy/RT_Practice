#pragma once

#include <ostream>

namespace rmrt {

	constexpr auto rgb_factor{ 255.999 };

	class Vec3 {
	public:
		Vec3() :e{ 0,0,0 } {}
		Vec3(double e0, double e1, double e2) :e{ e0, e1, e2 } {}
		double x() const;
		double y() const;
		double z() const;
		double length() const;
		double length_squared() const;

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
	using point3 = Vec3;
	using color = Vec3;

	// The utility functions for Vec3
	std::ostream& operator<<(std::ostream& out, const Vec3& v);
	Vec3 operator+(const Vec3& u, const Vec3& v);
	Vec3 operator-(const Vec3& u, const Vec3& v);
	Vec3 operator*(const Vec3& u, const Vec3& v);
	Vec3 operator*(double t, const Vec3& v);
	Vec3 operator*(const Vec3& v, double t);
	Vec3 operator/(Vec3 v, double t);

	// Scalar
	double dot(const Vec3& u, const Vec3& v);

	Vec3 cross(const Vec3& u, const Vec3& v);
	Vec3 unit_vector(Vec3 v);

	void write_color(std::ostream& out, color pixel_color);
}
