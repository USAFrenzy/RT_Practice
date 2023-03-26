
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
	*                                              ----------------------- x
	*   2) To find the final length value given vector points, we plot the points on the graph
	*   3) We have the height of the vector triangle as our 'z' axis and the width of our vector triangle as our 'x' or 'y' axis
	*   4) To solve for the hypotenuse, our vector legnth, we need to first find the base value of our vector triangle
	*   5) To solve for the base value, we need to create an intermediary right triangle using the other points of our vector
	*   6) We then solve for the intermediatary right triangle formed between the graphs at origin ---> x  ---> y
	*   7) Once we found the hypotenuse value of the intermediatary right triangle, that becomes the base of the vector triangle 
	*   8) The formula then becomes:
	*                _____________________________________________
	*     Length =   | (    _____________  )^2
	*              v |(   v\    x^2 + y2   )     +     (z^2)        , where the first half with the squared square-root  cancels out and we're left with : 
	 *   
	 *               ____________________________
	 *   Length =   v\ (x^2) + (y^2 )+ (z^2)
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

}
