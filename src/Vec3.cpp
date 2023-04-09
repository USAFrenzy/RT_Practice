
#include <RMRT/Vec3.h>
#include <RMRT/RMRT.h>

#include <cmath>

namespace rmrt {

	float Vec3::X() const
	{
		return e[0];
	}

	float Vec3::Y() const
	{
		return e[1];
	}

	float Vec3::Z() const
	{
		return e[2];
	}

	// Pythagorean's theorem for vec length
	/*********************************************************************************************************************************
	*  Given that it's been a decade since I've done any vector math, the methodology goes as follows:
	*
	*  1) We have a vector at some point (x, y, z)
	*                                        z  \       /y
	*                                            \    /
	*                                             \  /
	*                                              \/
	*                                              --------------- x
	*
	*   2) To find the final length value given vector points, we plot the points on the graph
	*   3) We have the height of the vector triangle as our 'z' axis and the width of our vector triangle as our 'x' or 'y' axis
	*   4) To solve for the hypotenuse, our vector legnth, we need to first find the base value of our vector triangle
	*   5) To solve for the base value, we need to create an intermediary right triangle using the other points of our vector
	*   6) We then solve for the intermediatary right triangle formed between the graphs at origin ---> x  ---> y
	*   7) Once we found the hypotenuse value of the intermediatary right triangle, that becomes the base of the vector triangle
	*   8) The formula then becomes:
	*                _____________________________________________
	*     Length =   | (    _____________  )^2
	*              v | (   v|    x^2 + y2  )    +   (z^2)           ,
	*     where the first half with the squared square-root  cancels out and we're left with :
	*               ____________________________
	*   Length =   v| (x^2) + (y^2 )+ (z^2)
	*
	*********************************************************************************************************************************/
	float Vec3::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	float Vec3::LengthSquared() const
	{
		return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
	}

	bool Vec3::NearZero() const
	{
		const auto s = 1e-8;
		return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
	}

	Vec3 Vec3::Random()
	{
		return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
	}

	Vec3 Vec3::Random(float min, float max)
	{
		return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
	}

	Vec3 RandomInUnitSphere()
	{
		for (;;) {
			auto p{ Vec3::Random(-1, 1) };
			if (p.LengthSquared() < 1.0) return p;
			continue;
		}
	}

	void Vec3::Clear() {
		e[0] = e[1] = e[2] = 0.0;
	}

	Vec3 rmrt::RandomUnitVector()
	{
		// The original call called "UnitVector(RandomInUnitSphere())"; I believe just directly looping and dividing into 
		// itself instead of producing a new register load and divide would be more effiecient as a low-hanging fruit here,
		// however, the extra variable used to store the length squared result might negate that change. At the same time 
		// though, it should be a net-benefit since the original loop would have basically called LengthSquared() twice 
		// before taking the sqaure root anyways.

		// return UnitVector(RandomInUnitSphere());

		for (;;) {
			auto p{ Vec3::Random(-1, 1) };
			if (const auto result{ p.LengthSquared() }; result < 1.0) 	return p /= std::sqrt(result);
			continue;
		}
	}

	Vec3 Reflect(const Vec3& v, const Vec3& n)
	{
		return v - (2 * n * Dot(v, n));
	}

	Vec3 Vec3::operator-() const
	{
		return Vec3(-e[0], -e[1], -e[2]);
	}

	float Vec3::operator[](int i) const
	{
		return e[i];
	}

	float& Vec3::operator[](int i)
	{
		return e[i];
	}

	Vec3& Vec3::operator+=(const Vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	Vec3& Vec3::operator*=(const float t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	Vec3& Vec3::operator/=(const float t)
	{
		return *this *= 1 / t;
	}

	// The utility functions
	std::ostream& operator<<(std::ostream& out, const Vec3& v)
	{
		return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
	}

	Vec3 operator+(const Vec3& u, const Vec3& v)
	{
		return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
	}

	Vec3 operator-(const Vec3& u, const Vec3& v)
	{
		return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	}

	Vec3 operator*(const Vec3& u, const Vec3& v)
	{
		return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
	}

	Vec3 operator*(float t, const Vec3& v)
	{
		return Vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	Vec3 operator*(const Vec3& v, float t)
	{
		return t * v;
	}

	Vec3 operator/(Vec3 v, float t)
	{
		return (1 / t) * v;
	}

	// Scalar
	float Dot(const Vec3& u, const Vec3& v)
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
	*  2) We then find the determinates by taking each component multiplied by its respective 2D matrix by x-multiplying
	*     (subtracting the second term from the first) each 2D matrix by the corresponding 3D component factor:
	*     (  |  b1  c1  |        )      (  |  a1  c1  |         )     (  |  a1  b1  |  )         )
	*     (  |  b2  c2  |  * i   )   -  (  |  a2  c2  |   *  j  )  +  (  |  a2  b2  |  )   *  k  )   ---->
	*     a  x  b  =  ((( b1*c2)-(c1*b2) )* i) - ((( a1*c2)-(c1*a2) )* j)  + ((( a1*b2)-(b1*a2) )* k)
	*  3) The only difference here, is that instead of the full calculation, we are just creating and returning a Vec3 object with the computed values.
	*************************************************************************************************************************/
	Vec3 Cross(const Vec3& u, const Vec3& v)
	{
		return Vec3(
			((u.e[1] * v.e[2]) - (u.e[2] * v.e[1])),
			((u.e[2] * v.e[0]) - (u.e[0] * v.e[2])),
			((u.e[0] * v.e[1]) - (u.e[1] * v.e[0]))
		);
	}

	Vec3  UnitVector(Vec3 v)
	{
		return v / v.Length();
	}

	// Takes into consideration Snell's Law ( n*sin0 = n'*sin0' ) where:
	// both 0 & 0' are angles from the normal and both n and n' are the refractive indices
	// 1) To solve for the direction of the refracted ray, solve for sin0'
	//    This leaves us with sin0'=n/n'*sin0 where the refracted rays can be split into their |_ and || counterparts
	//    This now leaves us with two ray functions: A) R' = n/n'(R + cos0*n)   and   B) R'|| = - sqrt(1 - |R'|_ |^2*n)
	// 2) The dot product between two vectors can be simplified as the cosine angle between them to get: a*b = cos0
	// 3) This leaves the final equation as: R'|_ = n/n' * (R + (-R*n)*n)
	Vec3 rmrt::Refract(const Vec3& uv, const Vec3& n, float etai_over_etat)
	{
		auto cosineTheta{ fmin(Dot(-uv, n), 1.0f) };
		Vec3 perpendicularRayOut{ etai_over_etat * (uv + (cosineTheta * n)) };
		Vec3 parallelRayOut{ -sqrt(fabs(1.0f - perpendicularRayOut.LengthSquared())) * n };
		return perpendicularRayOut += parallelRayOut;
	}


}
