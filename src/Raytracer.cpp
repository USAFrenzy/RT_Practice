
#include <RMRT/Raytracer.h>

#include <cmath>

namespace rmrt {

	double vec3::x() const
	{
		return e[0];
	}

	double vec3::y() const
	{
		return e[1];
	}

	double vec3::z() const
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
	double vec3::length() const
	{
		return std::sqrt(length_squared());
	}

	double vec3::length_squared() const
	{
		return (e[0] * e[0]) + (e[1] * e[1]) + (e[2] * e[2]);
	}

	vec3 vec3::operator-() const
	{
		return vec3(-e[0], -e[1], -e[2]);
	}

	double vec3::operator[](int i) const
	{
		return e[i];
	}

	double& vec3::operator[](int i)
	{
		return e[i];
	}

	vec3& vec3::operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& vec3::operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& vec3::operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	// The utility functions
	std::ostream& operator<<(std::ostream& out, const vec3& v)
	{
		return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
	}

	vec3 operator+(const vec3& u, const vec3& v)
	{
		return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
	}

	vec3 operator-(const vec3& u, const vec3& v)
	{
		return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
	}

	vec3 operator*(const vec3& u, const vec3& v)
	{
		return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
	}

	vec3 operator*(double t, const vec3& v)
	{
		return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
	}

	vec3 operator*(const vec3& v, double t)
	{
		return t * v;
	}

	vec3 operator/(vec3 v, double t)
	{
		return (1 / t) * v;
	}

	// Scalar
	double dot(const vec3& u, const vec3& v)
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
	*************************************************************************************************************************/
	vec3 cross(const vec3& u, const vec3& v)
	{
		return vec3(
			((u.e[1] * v.e[2]) - (u.e[2] * v.e[1])),
			((u.e[2] * v.e[0]) - (u.e[0] * v.e[2])),
			((u.e[0] * v.e[1]) - (u.e[1] * v.e[0]))
		);
	}

	vec3 unit_vector(vec3 v)
	{
		return v / v.length();
	}
	void write_color(std::ostream& out, color pixel_color)
	{
		// This basically does what the initial code in the 2.1 module of 'Raytracing In One Weekend' accomplished, except it now uses the ostream class to write to the console (This is from module 3.3)
		out << static_cast<int>(rgb_factor * pixel_color.x()) << ' ' << static_cast<int>(rgb_factor * pixel_color.y()) << ' ' << static_cast<int>(rgb_factor * pixel_color.z()) << '\n';
	}
}
