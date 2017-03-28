#ifndef __PIXEL_RAIN_DEFAULTS__HEADER__INCLUDED__
#define __PIXEL_RAIN_DEFAULTS__HEADER__INCLUDED__

#include <vector.h>
#include <pixelrain.h>
#include <math.h>
#include <random>
#include <iostream>

/// -----------------
/// DATATYPES
/// -----------------

/**
 * \brief pixel type for a three component color
 */
typedef Vect3f Type_Color3;

/// ------------------
/// COMPARATORS
/// ------------------

template<typename ScalarT>
struct ScalingVect3Comparator
{
private:
	const ScalarT scaleX_;
	const ScalarT scaleY_;
	const ScalarT scaleZ_;

public:
	ScalingVect3Comparator(ScalarT scaleX, ScalarT scaleY, ScalarT scaleZ)
		: scaleX_(scaleX), scaleY_(scaleY), scaleZ_(scaleZ)
	{ }
	ScalingVect3Comparator()
		: ScalingVect3Comparator(1, 1, 1)
	{ }

	float operator() (const Vect<3, ScalarT>& c1, const Vect<3, ScalarT>& c2) const 
	{
		double v = 0;
		v += scaleX_ * (c1.x - c2.x) * (c1.x - c2.x);
		v += scaleY_ * (c1.y - c2.y) * (c1.y - c2.y);
		v += scaleZ_ * (c1.z - c2.z) * (c1.z - c2.z);
		return sqrtf((float)v);
	}
};

/**
 * \brief the default comparator for three-component color types
 */
typedef ScalingVect3Comparator<float> Comparator_Color3;


/// ------------------
/// Random Generators
/// ------------------

template<typename ScalarT>
struct Vect3RandomGenerator
{
private:
	std::default_random_engine engine_;
	std::uniform_real_distribution<ScalarT> distrX_;
	std::uniform_real_distribution<ScalarT> distrY_;
	std::uniform_real_distribution<ScalarT> distrZ_;

public:
	Vect3RandomGenerator(ScalarT minX, ScalarT maxX, ScalarT minY, ScalarT maxY, ScalarT minZ, ScalarT maxZ)
		: distrX_(minX, maxX), distrY_(minY, maxY), distrZ_(minZ, maxZ)
	{ }
	Vect3RandomGenerator()
		: Vect3RandomGenerator(0, 1, 0, 1, 0, 1)
	{ }

	Vect<3, ScalarT> operator() ()
	{
		return Vect<3, ScalarT>(
			distrX_(engine_),
			distrY_(engine_),
			distrZ_(engine_)
		);
	}
};

/**
 * \brief The default random generator for three-component color types.
 */
typedef Vect3RandomGenerator<float> Random_Color3;


/// -------------------
/// CONVERTERS
/// -------------------

/**
 *\brief The default converter for Type_Color3 representing RGB values
 */
struct ConverterRGB
{
public:
	Vect4f operator() (const Type_Color3& color) const
	{
		return Vect4f(color, 1);
	}
};

/**
*\brief The default converter for Type_Color3 representing HSV values
*/
//struct ConverterHSV
//{
//public:
//	Vect4f operator() (const Type_Color3& color) const
//	{
//		return Vect4f(color, 1);
//	}
//};

/// ---------------------
/// ProgressListener
/// ---------------------

/**
 * \brief a progress listener that logs to std::cout
 */
struct CoutProgressListener
{
public:
	void operator() (float percentage, size_t remaining) const
	{
		if (remaining % 1000 == 0)
		{
			std::cout << "Remaining: " << remaining << "  (" << (percentage * 100) << "%)" << std::endl;
		}
	}
};

#endif