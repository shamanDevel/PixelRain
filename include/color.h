#ifndef __PIXEL_RAIN_COLOR__HEADER__INCLUDED__
#define __PIXEL_RAIN_COLOR__HEADER__INCLUDED__

#define _USE_MATH_DEFINES

#include <vector.h>
#include <math.h>

class ColorConverter
{
private:
	static float frac(float x)
	{
		return x - floor(x);
	}

public:
	static Vect3f saturate(const Vect3f& v)
	{
		return Clamp(v, Vect3f(0, 0, 0), Vect3f(1, 1, 1));
	}

	static Vect3f HUEtoRGB(float hue)
	{
		float r = fabs(hue * 6 - 3) - 1;
		float g = 2 - fabs(hue * 6 - 2);
		float b = 2 - fabs(hue * 6 - 4);
		return saturate(Vect3f(r, g, b));
	}

	static Vect3f HSVtoRGB(const Vect3f& hsv)
	{
		Vect3f rgb = HUEtoRGB(hsv.x);
		return ((rgb - Vect3f(1)) * hsv.y + Vect3f(1)) * hsv.z;
	}

	static Vect3f HSLtoRGB(const Vect3f& hsl)
	{
		Vect3f rgb = HUEtoRGB(hsl.x);
		float c = (1 - fabs(2 * hsl.z - 1)) * hsl.y;
		return (rgb - Vect3f(0.5f)) * c + Vect3f(hsl.z);
	}

	static Vect3f HCVtoRGB(const Vect3f& hcy)
	{
		static const Vect3f HCVwts(0.299, 0.587, 0.114);
		Vect3f rgb = HUEtoRGB(hcy.x);
		float z = Dot(rgb, HCVwts);
		float y = hcy.y;
		if (hcy.z < z)
			y *= hcy.z / z;
		else if (z < 1)
			y *= (1 - hcy.z) / (1 - z);
		return (rgb - Vect3f(z)) * y + Vect3f(z);
	}

	static Vect3f HCLtoRGB(const Vect3f& hcl)
	{
		static const float HCLgamma = 3;
		static const float HCLy0 = 100;
		static const float HCLmaxL = 0.530454533963517;
		static const float PI = M_PI;
		Vect3f rgb(0.0f);
		if (hcl.z != 0) {
			float h = hcl.x;
			float c = hcl.y;
			float l = hcl.z * HCLmaxL;
			float q = exp((1 - c / (2 * l)) * (HCLgamma / HCLy0));
			float u = (2 * l - c) / (2 * q - 1);
			float v = c / q;
			float t = tan((h + fmin(frac(2 * h) / 4, frac(-2 * h) / 8)) * PI * 2);
			h *= 6;
			if (h <= 1) {
				rgb.x = 1;
				rgb.y = t / (1 + t);
			}
			else if (h <= 2) {
				rgb.x = (1 + t) / t;
				rgb.y = 1;
			}
			else if (h <= 3) {
				rgb.y = 1;
				rgb.z = 1 + t;
			}
			else if (h <= 4) {
				rgb.y = 1 / (1 + t);
				rgb.z = 1;
			} else if (h <= 5) {
				rgb.x = -1 / t;
				rgb.z = 1;
			} else {
				rgb.x = 1;
				rgb.z = -t;
			}
			rgb = rgb * v + Vect3f(u);
		}
		return saturate(rgb);
	}
};

#endif