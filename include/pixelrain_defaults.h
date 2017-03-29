#ifndef __PIXEL_RAIN_DEFAULTS__HEADER__INCLUDED__
#define __PIXEL_RAIN_DEFAULTS__HEADER__INCLUDED__

#include <vector.h>
#include <pixelrain.h>
#include <color.h>

#include <math.h>
#include <random>
#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

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
* \brief the default comparator for three-component color types.
*/
typedef ScalingVect3Comparator<float> Comparator_Color3;

template<typename ScalarT>
struct ScalingHueVect3Comparator
{
private:
	const ScalarT scaleX_;
	const ScalarT scaleY_;
	const ScalarT scaleZ_;

public:
	ScalingHueVect3Comparator(ScalarT scaleX, ScalarT scaleY, ScalarT scaleZ)
		: scaleX_(scaleX), scaleY_(scaleY), scaleZ_(scaleZ)
	{
	}
	ScalingHueVect3Comparator()
		: ScalingHueVect3Comparator(1, 1, 1)
	{
	}

	float operator() (const Vect<3, ScalarT>& c1, const Vect<3, ScalarT>& c2) const
	{
		double v = 0;
		v += scaleX_ * std::min({
			(c1.x - c2.x) * (c1.x - c2.x),
			(c1.x - c2.x + 1) * (c1.x - c2.x + 1),
			(c1.x - c2.x - 1) * (c1.x - c2.x - 1) });
		v += scaleY_ * (c1.y - c2.y) * (c1.y - c2.y);
		v += scaleZ_ * (c1.z - c2.z) * (c1.z - c2.z);
		return sqrtf((float)v);
	}
};

/**
 * \brief the default comparator for three-component color types where the first component represents hue.
 * Hue needs special treatment: it is periodic. This means, the difference between hue 0.1 and hue 0.9 is not 0.8 but 0.2.
 */
typedef ScalingHueVect3Comparator<float> HueComparator_Color3;


/// ------------------
/// Random Generators
/// ------------------

template<typename ScalarT>
struct Vect3RandomGenerator
{
public:
	typedef Vect<3, ScalarT> pixel_t;

private:
	std::default_random_engine engine_;
	std::uniform_real_distribution<ScalarT> distrX_;
	std::uniform_real_distribution<ScalarT> distrY_;
	std::uniform_real_distribution<ScalarT> distrZ_;

public:
	Vect3RandomGenerator(ScalarT minX, ScalarT maxX, ScalarT minY, ScalarT maxY, ScalarT minZ, ScalarT maxZ)
		: engine_(std::chrono::system_clock::now().time_since_epoch().count())
		, distrX_(minX, maxX), distrY_(minY, maxY), distrZ_(minZ, maxZ)
	{ }
	Vect3RandomGenerator()
		: Vect3RandomGenerator(0, 1, 0, 1, 0, 1)
	{ }

	pixel_t operator() ()
	{
		Vect<3, ScalarT> v(
			distrX_(engine_),
			distrY_(engine_),
			distrZ_(engine_)
		);
		if (v.x < 0) v.x += 1; //hue
		return v;
	}
};

/**
 * \brief The default random generator for three-component color types.
 */
typedef Vect3RandomGenerator<float> Random_Color3;

/**
 * \brief Computes a mixture of different random generators.
 *	Add generators with addGenerator(generator, weight).
 *	After all generators were added, normalize the weights with normalize().
 *	Only after then can this generator be used
 * \tparam T the random generators
 */
template<typename T>
class MixtureRandomGenerator
{
public:
	typedef typename T::pixel_t pixel_t;

private:
	std::vector<T> generators_;
	std::vector<float> weights_;
	std::default_random_engine engine_;
	std::uniform_real_distribution<float> distribution_;

public:
	MixtureRandomGenerator() 
		: engine_(std::chrono::system_clock::now().time_since_epoch().count())
	{}

	void addGenerator(const T& generator, float weight)
	{
		generators_.push_back(generator);
		weights_.push_back(weight);
	}

	void normalize()
	{
		assert(!weights_.empty());
		float sum = 0;
		for (float w : weights_) sum += w;
		float factor = 1 / sum;
		sum = 0;
		for (size_t i = 0; i < weights_.size(); ++i)
		{
			weights_[i] = sum + weights_[i] * factor;
			sum = weights_[i];
		}
	}

	pixel_t operator() ()
	{
		float f = distribution_(engine_);
		for (size_t i = 0; i < weights_.size()-1; ++i)
		{
			if (f < weights_[i])
			{
				return generators_[i]();
			}
		}
		return generators_[weights_.size() - 1]();
	}
};

/**
 * \brief A mixture of Random_Color3 generators
 */
typedef MixtureRandomGenerator<Random_Color3> MixtureRandom_Color3;

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

struct ConverterHCL
{
public:
	Vect4f operator() (const Type_Color3& color) const
	{
		Type_Color3 c(color);
		if (c.x < 0) c.x += 1; //hue
		return Vect4f(ColorConverter::HCLtoRGB(c), 1);
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