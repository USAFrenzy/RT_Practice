#pragma once

#include <ostream>

namespace rmrt {

	constexpr auto rgb_factor{ 255.999 };

	class vec3 {
	public:
		vec3() :e{ 0,0,0 } {}
		vec3(double e0, double e1, double e2) :e{ e0, e1, e2 } {}
		double x() const;
		double y() const;
		double z() const;
		double length() const;
		double length_squared() const;

		// operator overloads
		vec3 operator-() const;
		double operator[](int i) const;
		double& operator[](int i);
		vec3& operator +=(const vec3& v);
		vec3& operator*=(const double t);
		vec3& operator/=(const double t);


	public:
		double e[3];
	};
	using point3 = vec3;
	using color = vec3;

	// The utility functions for vec3
	std::ostream& operator<<(std::ostream& out, const vec3& v);
	vec3 operator+(const vec3 &u, const vec3& v);
	vec3 operator-(const vec3& u, const vec3& v);
	vec3 operator*(const vec3& u, const vec3& v);
	vec3 operator*(double t, const vec3& v);
	vec3 operator*(const vec3& v, double t);
	vec3 operator/(vec3 v, double t);

	// Scalar
	double dot(const vec3& u, const vec3& v);

	vec3 cross(const vec3&u, const vec3& v);
	vec3 unit_vector(vec3 v);

	void write_color(std::ostream& out, color pixel_color);
}
