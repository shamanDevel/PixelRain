/*************************************************************************************

Author: Christian Dick

Copyright (c) Christian Dick

mailto:dick@in.tum.de

*************************************************************************************/

#ifndef __TUM3D__VECTOR_H__
#define __TUM3D__VECTOR_H__


#include <cmath>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <vector>

template <int N, class T>
class Vect;


template <class T>
class Vect<1,T>
{
public:

	T x;

	Vect() { }
	Vect(const Vect<1,T>& v) : x(v.x) { }
	explicit Vect(const T& x) : x(x) { }
	explicit Vect(const T* p) : x(p[0]) { }
	template <int M, class S> explicit Vect(const Vect<M,S>& v) : x(T(v[0])) { }
	template <int M, class S> Vect(const Vect<M,S>& v, const T& s)
	{
		int M_ = M < 1 ? M : 1;
		for (int i = 0; i < M_; i++) { (&x)[i] = T(v[i]); }
		for (int i = M_; i < 1; i++) { (&x)[i] = s; }
	}

	T& operator[](int i) { return (&x)[i]; }
	const T& operator[](int i) const { return (&x)[i]; }

	void Clear() { x = T(0); }

	Vect<1,T>& operator=(const Vect<1,T>& v) { x = v.x; return *this; }

	Vect<1,T>& operator+=(const Vect<1,T>& v) { x += v.x; return *this; }
	Vect<1,T>& operator-=(const Vect<1,T>& v) { x -= v.x; return *this; }
	Vect<1,T>& operator*=(const T& s) { x *= s; return *this; }
	Vect<1,T>& operator*=(const Vect<1,T>& v) { x *= v.x; return *this; }
	Vect<1,T>& operator/=(const T& s) { x /= s; return *this; }
	Vect<1,T>& operator/=(const Vect<1,T>& v) { x /= v.x; return *this; }
	Vect<1,T>& operator%=(const T& s) { x %= s; return *this; }
	Vect<1,T>& operator%=(const Vect<1,T>& v) { x %= v.x; return *this; }
	Vect<1,T>& operator<<=(int n) { x <<= n; return *this; }
	Vect<1,T>& operator>>=(int n) { x >>= n; return *this; }
	Vect<1,T>& operator&=(const T& s) { x &= s; return *this; }
	Vect<1,T>& operator&=(const Vect<1,T>& v) { x &= v.x; return *this; }
	Vect<1,T>& operator|=(const T& s) { x |= s; return *this; }
	Vect<1,T>& operator|=(const Vect<1,T>& v) { x |= v.x; return *this; }
	Vect<1,T>& operator^=(const T& s) { x ^= s; return *this; }
	Vect<1,T>& operator^=(const Vect<1,T>& v) { x ^= v.x; return *this; }

	operator T*() { return &x; } // Cast to T*
	operator const T*() const { return &x; } // Cast to const T*

	T MinElem() const { return x; }
	T MaxElem() const { return x; }

	template <class Archive>
	void serialize(Archive & ar, const unsigned int version) { ar & x; }
};

template <class T> inline Vect<1,T> operator+(const Vect<1,T>& v) { return v; }
template <class T> inline Vect<1,T> operator+(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x + v2.x); }
template <class T> inline Vect<1,T> operator-(const Vect<1,T>& v) { return Vect<1,T>(-v.x); }
template <class T> inline Vect<1,T> operator-(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x - v2.x); }
template <class T> inline Vect<1,T> operator*(const T& s, const Vect<1,T>& v) { return Vect<1,T>(s * v.x); }
template <class T> inline Vect<1,T> operator*(const Vect<1,T>& v, const T& s) { return Vect<1,T>(v.x * s); }
template <class T> inline Vect<1,T> operator*(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x * v2.x); }
template <class T> inline Vect<1,T> operator/(const T& s, const Vect<1,T>& v) { return Vect<1,T>(s / v.x); }
template <class T> inline Vect<1,T> operator/(const Vect<1,T>& v, const T& s) { return Vect<1,T>(v.x / s); }
template <class T> inline Vect<1,T> operator/(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x / v2.x); }
template <class T> inline Vect<1,T> operator%(const Vect<1,T>& v, const T& s) { return Vect<1,T>(v.x % s); }
template <class T> inline Vect<1,T> operator%(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x % v2.x); }
template <class T> inline Vect<1,T> operator<<(const Vect<1,T>& v, int n) { return Vect<1,T>(v.x << n); }
template <class T> inline Vect<1,T> operator>>(const Vect<1,T>& v, int n) { return Vect<1,T>(v.x >> n); }
template <class T> inline Vect<1,T> operator&(const Vect<1,T>& v, const T& s) { return Vect<1,T>(v.x & s); }
template <class T> inline Vect<1,T> operator&(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x & v2.x); }
template <class T> inline Vect<1,T> operator|(const Vect<1,T>& v, const T& s) { return Vect<1,T>(v.x | s); }
template <class T> inline Vect<1,T> operator|(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x | v2.x); }
template <class T> inline Vect<1,T> operator^(const Vect<1,T>& v, const T& s) { return Vect<1,T>(v.x ^ s); }
template <class T> inline Vect<1,T> operator^(const Vect<1,T>& v1, const Vect<1,T>& v2) { return Vect<1,T>(v1.x ^ v2.x); }
template <class T> inline Vect<1,T> abs(const Vect<1,T>& v) { return Vect<1,T>(std::abs(v.x)); }

template <class T> inline bool operator==(const Vect<1,T>& v1, const Vect<1,T>& v2) { return v1.x == v2.x; }
template <class T> inline bool operator!=(const Vect<1,T>& v1, const Vect<1,T>& v2) { return v1.x != v2.x; }
template <class T> inline bool operator<(const Vect<1,T>& v1, const Vect<1,T>& v2) { return v1.x < v2.x; }
template <class T> inline bool operator<=(const Vect<1,T>& v1, const Vect<1,T>& v2) { return v1.x <= v2.x; }
template <class T> inline bool operator>(const Vect<1,T>& v1, const Vect<1,T>& v2) { return v1.x > v2.x; }
template <class T> inline bool operator>=(const Vect<1,T>& v1, const Vect<1,T>& v2) { return v1.x >= v2.x; }

template <class T> inline T Dot(const Vect<1,T>& v1, const Vect<1,T>& v2) { return v1.x * v2.x; }
template <class T> inline T Length(const Vect<1,T>& v) { return sqrt(v.x * v.x); }
template <class T> inline T LengthSqr(const Vect<1,T>& v) { return v.x * v.x; }

template <class T> inline Vect<1,T> Normalize(const Vect<1,T>& v)
{
	T length_1 = T(1.0) / sqrt(v.x * v.x);
	return Vect<1,T>(v.x * length_1);
}

template <class T> inline Vect<1,T> SafeNormalize(const Vect<1,T>& v)
{
	T length = sqrt(v.x * v.x);
	if (length != T(0.0))
	{
		T length_1 = T(1.0) / length;
		return Vect<1,T>(v.x * length_1);
	}
	else
	{
		return v;
	}
}

template <class T> inline Vect<1,T> Min(const Vect<1,T>& v1, const Vect<1,T>& v2)
{
	return Vect<1,T>(
		v2.x < v1.x ? v2.x : v1.x
		);
}

template <class T> inline Vect<1,T> Max(const Vect<1,T>& v1, const Vect<1,T>& v2)
{
	return Vect<1,T>(
		v1.x < v2.x ? v2.x : v1.x
		);
}

template <class T> inline Vect<1,T> Floor(const Vect<1,T>& v) { return Vect<1,T>(std::floor(v.x)); }
template <class T> inline Vect<1,T> Ceil(const Vect<1,T>& v) { return Vect<1,T>(std::ceil(v.x)); }

template <class T> inline Vect<1,T> MinClamp(const Vect<1,T>& v, const Vect<1,T>& vMin)
{
	return Vect<1,T>(
		v.x < vMin.x ? vMin.x : v.x
		);
}

template <class T> inline Vect<1,T> MaxClamp(const Vect<1,T>& v, const Vect<1,T>& vMax)
{
	return Vect<1,T>(
		vMax.x < v.x ? vMax.x : v.x
		);
}

template <class T> inline Vect<1,T> Clamp(const Vect<1,T>& v, const Vect<1,T>& vMin, const Vect<1,T>& vMax)
{
	return Vect<1,T>(
		v.x < vMin.x ? vMin.x : (vMax.x < v.x ? vMax.x : v.x)
		);
}

template <class T> inline std::ostream& operator<<(std::ostream& ost, const Vect<1,T>& v) { ost << v.x; return ost; }
template <class T> inline std::wostream& operator<<(std::wostream& wost, const Vect<1,T>& v) { wost << v.x; return wost; }
template <class T> inline std::istream& operator>>(std::istream& ist, Vect<1,T>& v) { Vect<1,T> tmp; if (ist >> tmp.x) { v = tmp; } return ist; }
template <class T> inline std::wistream& operator>>(std::wistream& wist, Vect<1,T>& v) { Vect<1,T> tmp; if (wist >> tmp.x) { v = tmp; } return wist; }


template <class T>
class Vect<2,T>
{
public:

	T x, y;

	Vect() { }
	Vect(const Vect<2,T>& v) : x(v.x), y(v.y) { }
	explicit Vect(const T& s) : x(s), y(s) { }
	Vect(const T& x, const T& y) : x(x), y(y) { }
	explicit Vect(const T* p) : x(p[0]), y(p[1]) { }
	template <int M, class S> explicit Vect(const Vect<M,S>& v) : x(T(v[0])), y(T(v[1])) { }
	template <int M, class S> Vect(const Vect<M,S>& v, const T& s)
	{
		int M_ = M < 2 ? M : 2;
		for (int i = 0; i < M_; i++) { (&x)[i] = T(v[i]); }
		for (int i = M_; i < 2; i++) { (&x)[i] = s; }
	}

	T& operator[](int i) { return (&x)[i]; }
	const T& operator[](int i) const { return (&x)[i]; }

	void Clear() { x = T(0); y = T(0); }

	Vect<2,T>& operator=(const Vect<2,T>& v) { x = v.x; y = v.y; return *this; }

	Vect<2,T>& operator+=(const Vect<2,T>& v) { x += v.x; y += v.y; return *this; }
	Vect<2,T>& operator-=(const Vect<2,T>& v) { x -= v.x; y -= v.y; return *this; }
	Vect<2,T>& operator*=(const T& s) { x *= s; y *= s; return *this; }
	Vect<2,T>& operator*=(const Vect<2,T>& v) { x *= v.x; y *= v.y; return *this; }
	Vect<2,T>& operator/=(const T& s) { x /= s; y /= s; return *this; }
	Vect<2,T>& operator/=(const Vect<2,T>& v) { x /= v.x; y /= v.y; return *this; }
	Vect<2,T>& operator%=(const T& s) { x %= s; y %= s; return *this; }
	Vect<2,T>& operator%=(const Vect<2,T>& v) { x %= v.x; y %= v.y; return *this; }
	Vect<2,T>& operator<<=(int n) { x <<= n; y <<= n; return *this; }
	Vect<2,T>& operator>>=(int n) { x >>= n; y >>= n; return *this; }
	Vect<2,T>& operator&=(const T& s) { x &= s; y &= s; return *this; }
	Vect<2,T>& operator&=(const Vect<2,T>& v) { x &= v.x; y &= v.y; return *this; }
	Vect<2,T>& operator|=(const T& s) { x |= s; y |= s; return *this; }
	Vect<2,T>& operator|=(const Vect<2,T>& v) { x |= v.x; y |= v.y; return *this; }
	Vect<2,T>& operator^=(const T& s) { x ^= s; y ^= s; return *this; }
	Vect<2,T>& operator^=(const Vect<2,T>& v) { x ^= v.x; y ^= v.y; return *this; }

	operator T*() { return &x; } // Cast to T*
	operator const T*() const { return &x; } // Cast to const T*

	T MinElem() const { return y < x ? y : x; }
	T MaxElem() const { return x < y ? y : x; }

	template <class Archive>
	void serialize(Archive & ar, const unsigned int version) { ar & x; ar & y; }
};

template <class T> inline Vect<2,T> operator+(const Vect<2,T>& v) { return v; }
template <class T> inline Vect<2,T> operator+(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x + v2.x, v1.y + v2.y); }
template <class T> inline Vect<2,T> operator-(const Vect<2,T>& v) { return Vect<2,T>(-v.x, -v.y); }
template <class T> inline Vect<2,T> operator-(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x - v2.x, v1.y - v2.y); }
template <class T> inline Vect<2,T> operator*(const T& s, const Vect<2,T>& v) { return Vect<2,T>(s * v.x, s * v.y); }
template <class T> inline Vect<2,T> operator*(const Vect<2,T>& v, const T& s) { return Vect<2,T>(v.x * s, v.y * s); }
template <class T> inline Vect<2,T> operator*(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x * v2.x, v1.y * v2.y); }
template <class T> inline Vect<2,T> operator/(const T& s, const Vect<2,T>& v) { return Vect<2,T>(s / v.x, s / v.y); }
template <class T> inline Vect<2,T> operator/(const Vect<2,T>& v, const T& s) { return Vect<2,T>(v.x / s, v.y / s); }
template <class T> inline Vect<2,T> operator/(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x / v2.x, v1.y / v2.y); }
template <class T> inline Vect<2,T> operator%(const Vect<2,T>& v, const T& s) { return Vect<2,T>(v.x % s, v.y % s); }
template <class T> inline Vect<2,T> operator%(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x % v2.x, v1.y % v2.y); }
template <class T> inline Vect<2,T> operator<<(const Vect<2,T>& v, int n) { return Vect<2,T>(v.x << n, v.y << n); }
template <class T> inline Vect<2,T> operator>>(const Vect<2,T>& v, int n) { return Vect<2,T>(v.x >> n, v.y >> n); }
template <class T> inline Vect<2,T> operator&(const Vect<2,T>& v, const T& s) { return Vect<2,T>(v.x & s, v.y & s); }
template <class T> inline Vect<2,T> operator&(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x & v2.x, v1.y & v2.y); }
template <class T> inline Vect<2,T> operator|(const Vect<2,T>& v, const T& s) { return Vect<2,T>(v.x | s, v.y | s); }
template <class T> inline Vect<2,T> operator|(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x | v2.x, v1.y | v2.y); }
template <class T> inline Vect<2,T> operator^(const Vect<2,T>& v, const T& s) { return Vect<2,T>(v.x ^ s, v.y ^ s); }
template <class T> inline Vect<2,T> operator^(const Vect<2,T>& v1, const Vect<2,T>& v2) { return Vect<2,T>(v1.x ^ v2.x, v1.y ^ v2.y); }
template <class T> inline Vect<2,T> abs(const Vect<2,T>& v) { return Vect<2,T>(std::abs(v.x), std::abs(v.y)); }

template <class T> inline bool operator==(const Vect<2,T>& v1, const Vect<2,T>& v2) { return v1.x == v2.x && v1.y == v2.y; }
template <class T> inline bool operator!=(const Vect<2,T>& v1, const Vect<2,T>& v2) { return v1.x != v2.x || v1.y != v2.y; }
template <class T> inline bool operator<(const Vect<2,T>& v1, const Vect<2,T>& v2) { return v1.x < v2.x && v1.y < v2.y; }
template <class T> inline bool operator<=(const Vect<2,T>& v1, const Vect<2,T>& v2) { return v1.x <= v2.x && v1.y <= v2.y; }
template <class T> inline bool operator>(const Vect<2,T>& v1, const Vect<2,T>& v2) { return v1.x > v2.x && v1.y; }
template <class T> inline bool operator>=(const Vect<2,T>& v1, const Vect<2,T>& v2) { return v1.x >= v2.x && v1.y >= v2.y; }

template <class T> inline T Dot(const Vect<2,T>& v1, const Vect<2,T>& v2) { return v1.x * v2.x + v1.y * v2.y; }
template <class T> inline T Length(const Vect<2,T>& v) { return sqrt(v.x * v.x + v.y * v.y); }
template <class T> inline T LengthSqr(const Vect<2,T>& v) { return v.x * v.x + v.y * v.y; }

template <class T> inline Vect<2,T> Normalize(const Vect<2,T>& v)
{
	T length_1 = T(1.0) / sqrt(v.x * v.x + v.y * v.y);
	return Vect<2,T>(v.x * length_1, v.y * length_1);
}

template <class T> inline Vect<2,T> SafeNormalize(const Vect<2,T>& v)
{
	T length = sqrt(v.x * v.x + v.y * v.y);
	if (length != T(0.0))
	{
		T length_1 = T(1.0) / length;
		return Vect<2,T>(v.x * length_1, v.y * length_1);
	}
	else
	{
		return v;
	}
}

template <class T> inline Vect<2,T> Min(const Vect<2,T>& v1, const Vect<2,T>& v2)
{
	return Vect<2,T>(
		v2.x < v1.x ? v2.x : v1.x,
		v2.y < v1.y ? v2.y : v1.y
		);
}

template <class T> inline Vect<2,T> Max(const Vect<2,T>& v1, const Vect<2,T>& v2)
{
	return Vect<2,T>(
		v1.x < v2.x ? v2.x : v1.x,
		v1.y < v2.y ? v2.y : v1.y
		);
}

template <class T> inline Vect<2,T> Floor(const Vect<2,T>& v) { return Vect<2,T>(std::floor(v.x), std::floor(v.y)); }
template <class T> inline Vect<2,T> Ceil(const Vect<2,T>& v) { return Vect<2,T>(std::ceil(v.x), std::ceil(v.y)); }

template <class T> inline Vect<2,T> MinClamp(const Vect<2,T>& v, const Vect<2,T>& vMin)
{
	return Vect<2,T>(
		v.x < vMin.x ? vMin.x : v.x,
		v.y < vMin.y ? vMin.y : v.y
		);
}

template <class T> inline Vect<2,T> MaxClamp(const Vect<2,T>& v, const Vect<2,T>& vMax)
{
	return Vect<2,T>(
		vMax.x < v.x ? vMax.x : v.x,
		vMax.y < v.y ? vMax.y : v.y
		);
}

template <class T> inline Vect<2,T> Clamp(const Vect<2,T>& v, const Vect<2,T>& vMin, const Vect<2,T>& vMax)
{
	return Vect<2,T>(
		v.x < vMin.x ? vMin.x : (vMax.x < v.x ? vMax.x : v.x),
		v.y < vMin.y ? vMin.y : (vMax.y < v.y ? vMax.y : v.y)
		);
}

template <class T> inline Vect<2, T> Lerp(const T& f, const Vect<2, T>& a0, const Vect<2, T>& a1)
{
	return Vect<2, T>(
		(1 - f)*a0.x + f*a1.x,
		(1 - f)*a0.y + f*a1.y
		);
}
template <class T> inline Vect<2, T> Lerp3(const Vect<3, T>& f,
	const Vect<2, T>& a000, const Vect<2, T>& a001, const Vect<2, T>& a010, const Vect<2, T>& a011,
	const Vect<2, T>& a100, const Vect<2, T>& a101, const Vect<2, T>& a110, const Vect<2, T>& a111)
{
	return Lerp(f.x,
		Lerp(f.y, Lerp(f.z, a000, a001), Lerp(f.z, a010, a011)),
		Lerp(f.y, Lerp(f.z, a100, a101), Lerp(f.z, a110, a111))
		);
}

template <class T> inline std::ostream& operator<<(std::ostream& ost, const Vect<2,T>& v) { ost << v.x << ' ' << v.y; return ost; }
template <class T> inline std::wostream& operator<<(std::wostream& wost, const Vect<2,T>& v) { wost << v.x << L' ' << v.y; return wost; }
template <class T> inline std::istream& operator>>(std::istream& ist, Vect<2,T>& v) { Vect<2,T> tmp; if (ist >> tmp.x >> tmp.y) { v = tmp; } return ist; }
template <class T> inline std::wistream& operator>>(std::wistream& wist, Vect<2,T>& v) { Vect<2,T> tmp; if (wist >> tmp.x >> tmp.y) { v = tmp; } return wist; }


template <class T>
class Vect<3,T>
{
public:

	T x, y, z;

	Vect() { }
	Vect(const Vect<3,T>& v) : x(v.x), y(v.y), z(v.z) { }
	explicit Vect(const T& s) : x(s), y(s), z(s) { }
	Vect(const T& x, const T& y, const T& z) : x(x), y(y), z(z) { }
	explicit Vect(const T* p) : x(p[0]), y(p[1]), z(p[2]) { }
	template <int M, class S> explicit Vect(const Vect<M,S>& v) : x(T(v[0])), y(T(v[1])), z(T(v[2])) { }
	template <int M, class S> Vect(const Vect<M,S>& v, const T& s)
	{
		int M_ = M < 3 ? M : 3;
		for (int i = 0; i < M_; i++) { (&x)[i] = T(v[i]); }
		for (int i = M_; i < 3; i++) { (&x)[i] = s; }
	}

	T& operator[](int i) { return (&x)[i]; }
	const T& operator[](int i) const { return (&x)[i]; }

	void Clear() { x = T(0); y = T(0); z = T(0); }

	Vect<3,T>& operator=(const Vect<3,T>& v) { x = v.x; y = v.y; z = v.z; return *this; }

	Vect<3,T>& operator+=(const Vect<3,T>& v) { x += v.x; y += v.y; z += v.z; return *this; }
	Vect<3,T>& operator-=(const Vect<3,T>& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
	Vect<3,T>& operator*=(const T& s) { x *= s; y *= s; z *= s; return *this; }
	Vect<3,T>& operator*=(const Vect<3,T>& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
	Vect<3,T>& operator/=(const T& s) { x /= s; y /= s; z /= s; return *this; }
	Vect<3,T>& operator/=(const Vect<3,T>& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }
	Vect<3,T>& operator%=(const T& s) { x %= s; y %= s; z %= s; return *this; }
	Vect<3,T>& operator%=(const Vect<3,T>& v) { x %= v.x; y %= v.y; z %= v.z; return *this; }
	Vect<3,T>& operator<<=(int n) { x <<= n; y <<= n; z <<= n; return *this; }
	Vect<3,T>& operator>>=(int n) { x >>= n; y >>= n; z >>= n; return *this; }
	Vect<3,T>& operator&=(const T& s) { x &= s; y &= s; z &= s; return *this; }
	Vect<3,T>& operator&=(const Vect<3,T>& v) { x &= v.x; y &= v.y; z &= v.z; return *this; }
	Vect<3,T>& operator|=(const T& s) { x |= s; y |= s; z |= s; return *this; }
	Vect<3,T>& operator|=(const Vect<3,T>& v) { x |= v.x; y |= v.y; z |= v.z; return *this; }
	Vect<3,T>& operator^=(const T& s) { x ^= s; y ^= s; z ^= s; return *this; }
	Vect<3,T>& operator^=(const Vect<3,T>& v) { x ^= v.x; y ^= v.y; z ^= v.z; return *this; }

	operator T*() { return &x; } // Cast to T*
	operator const T*() const { return &x; } // Cast to const T*

	T MinElem() const { T res = x; if (y < res) res = y; if (z < res) res = z; return res; }
	T MaxElem() const { T res = x; if (res < y) res = y; if (res < z) res = z; return res; }

	Vect<2, T> xy() const { return Vect<2, T>(x, y); }

	template <class Archive>
	void serialize(Archive & ar, const unsigned int version) { ar & x; ar & y; ar & z; }
};

template <class T> inline Vect<3,T> operator+(const Vect<3,T>& v) { return v; }
template <class T> inline Vect<3,T> operator+(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }
template <class T> inline Vect<3,T> operator-(const Vect<3,T>& v) { return Vect<3,T>(-v.x, -v.y, -v.z); }
template <class T> inline Vect<3,T> operator-(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }
template <class T> inline Vect<3,T> operator*(const T& s, const Vect<3,T>& v) { return Vect<3,T>(s * v.x, s * v.y, s * v.z); }
template <class T> inline Vect<3,T> operator*(const Vect<3,T>& v, const T& s) { return Vect<3,T>(v.x * s, v.y * s, v.z * s); }
template <class T> inline Vect<3,T> operator*(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }
template <class T> inline Vect<3,T> operator/(const T& s, const Vect<3,T>& v) { return Vect<3,T>(s / v.x, s / v.y, s / v.z); }
template <class T> inline Vect<3,T> operator/(const Vect<3,T>& v, const T& s) { return Vect<3,T>(v.x / s, v.y / s, v.z / s); }
template <class T> inline Vect<3,T> operator/(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }
template <class T> inline Vect<3,T> operator%(const Vect<3,T>& v, const T& s) { return Vect<3,T>(v.x % s, v.y % s, v.z % s); }
template <class T> inline Vect<3,T> operator%(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z); }
template <class T> inline Vect<3,T> operator<<(const Vect<3,T>& v, int n) { return Vect<3,T>(v.x << n, v.y << n, v.z << n); }
template <class T> inline Vect<3,T> operator>>(const Vect<3,T>& v, int n) { return Vect<3,T>(v.x >> n, v.y >> n, v.z >> n); }
template <class T> inline Vect<3,T> operator&(const Vect<3,T>& v, const T& s) { return Vect<3,T>(v.x & s, v.y & s, v.z & s); }
template <class T> inline Vect<3,T> operator&(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z); }
template <class T> inline Vect<3,T> operator|(const Vect<3,T>& v, const T& s) { return Vect<3,T>(v.x | s, v.y | s, v.z | s); }
template <class T> inline Vect<3,T> operator|(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z); }
template <class T> inline Vect<3,T> operator^(const Vect<3,T>& v, const T& s) { return Vect<3,T>(v.x ^ s, v.y ^ s, v.z ^ s); }
template <class T> inline Vect<3,T> operator^(const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z); }
template <class T> inline Vect<3,T> abs(const Vect<3,T>& v) { return Vect<3,T>(std::abs(v.x), std::abs(v.y), std::abs(v.z)); }
template <class T> inline Vect<3,T> operator!(const Vect<3,T>& v) { return Vect<3,T>(!v.x, !v.y, !v.z); }

template <class T> inline bool operator==(const Vect<3,T>& v1, const Vect<3,T>& v2) { return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z; }
template <class T> inline bool operator!=(const Vect<3,T>& v1, const Vect<3,T>& v2) { return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z; }
template <class T> inline bool operator<(const Vect<3,T>& v1, const Vect<3,T>& v2) { return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z; }
template <class T> inline bool operator<=(const Vect<3,T>& v1, const Vect<3,T>& v2) { return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z; }
template <class T> inline bool operator>(const Vect<3,T>& v1, const Vect<3,T>& v2) { return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z; }
template <class T> inline bool operator>=(const Vect<3,T>& v1, const Vect<3,T>& v2) { return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z; }

template <class T> inline Vect<3,T> ConditionalAssign(const Vect<3,bool>& b, const Vect<3,T>& v1, const Vect<3,T>& v2) { return Vect<3,T>(b.x ? v1.x : v2.x, b.y ? v1.y : v2.y, b.z ? v1.z : v2.z); }

template <class T> inline T Dot(const Vect<3,T>& v1, const Vect<3,T>& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
template <class T> inline T Length(const Vect<3,T>& v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }
template <class T> inline T LengthSqr(const Vect<3,T>& v) { return v.x * v.x + v.y * v.y + v.z * v.z; }

template <class T> inline Vect<3,T> Normalize(const Vect<3,T>& v)
{
	T length_1 = T(1.0) / sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return Vect<3,T>(v.x * length_1, v.y * length_1, v.z * length_1);
}

template <class T> inline Vect<3,T> SafeNormalize(const Vect<3,T>& v)
{
	T length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length != T(0.0))
	{
		T length_1 = T(1.0) / length;
		return Vect<3,T>(v.x * length_1, v.y * length_1, v.z * length_1);
	}
	else
	{
		return v;
	}
}

template <class T> inline Vect<3,T> Min(const Vect<3,T>& v1, const Vect<3,T>& v2)
{
	return Vect<3,T>(
		v2.x < v1.x ? v2.x : v1.x,
		v2.y < v1.y ? v2.y : v1.y,
		v2.z < v1.z ? v2.z : v1.z
		);
}

template <class T> inline Vect<3,T> Max(const Vect<3,T>& v1, const Vect<3,T>& v2)
{
	return Vect<3,T>(
		v1.x < v2.x ? v2.x : v1.x,
		v1.y < v2.y ? v2.y : v1.y,
		v1.z < v2.z ? v2.z : v1.z
		);
}

template <class T> inline Vect<3,T> Floor(const Vect<3,T>& v) { return Vect<3,T>(std::floor(v.x), std::floor(v.y), std::floor(v.z)); }
template <class T> inline Vect<3,T> Ceil(const Vect<3,T>& v) { return Vect<3,T>(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z)); }

template <class T> inline Vect<3,T> MinClamp(const Vect<3,T>& v, const Vect<3,T>& vMin)
{
	return Vect<3,T>(
		v.x < vMin.x ? vMin.x : v.x,
		v.y < vMin.y ? vMin.y : v.y,
		v.z < vMin.z ? vMin.z : v.z
		);
}

template <class T> inline Vect<3,T> MaxClamp(const Vect<3,T>& v, const Vect<3,T>& vMax)
{
	return Vect<3,T>(
		vMax.x < v.x ? vMax.x : v.x,
		vMax.y < v.y ? vMax.y : v.y,
		vMax.z < v.z ? vMax.z : v.z
		);
}

template <class T> inline Vect<3,T> Clamp(const Vect<3,T>& v, const Vect<3,T>& vMin, const Vect<3,T>& vMax)
{
	return Vect<3,T>(
		v.x < vMin.x ? vMin.x : (vMax.x < v.x ? vMax.x : v.x),
		v.y < vMin.y ? vMin.y : (vMax.y < v.y ? vMax.y : v.y),
		v.z < vMin.z ? vMin.z : (vMax.z < v.z ? vMax.z : v.z)
		);
}

//template <class T> inline std::ostream& operator<<(std::ostream& ost, const Vect<3,T>& v) { ost << v.x << ' ' << v.y << ' ' << v.z; return ost; }
//template <class T> inline std::wostream& operator<<(std::wostream& wost, const Vect<3,T>& v) { wost << v.x << L' ' << v.y << L' ' << v.z; return wost; }
template <class T> inline std::ostream& operator<<(std::ostream& ost, const Vect<3, T>& v) { ost << "(" << v.x << ',' << v.y << ',' << v.z << ")"; return ost; }
template <class T> inline std::wostream& operator<<(std::wostream& wost, const Vect<3, T>& v) { wost << L"(" << v.x << L',' << v.y << L',' << v.z << L")"; return wost; }
template <class T> inline std::istream& operator>>(std::istream& ist, Vect<3,T>& v) { Vect<3,T> tmp; if (ist >> tmp.x >> tmp.y >> tmp.z) { v = tmp; } return ist; }
template <class T> inline std::wistream& operator>>(std::wistream& wist, Vect<3,T>& v) { Vect<3,T> tmp; if (wist >> tmp.x >> tmp.y >> tmp.z) { v = tmp; } return wist; }

template <class T>
inline Vect<3,T> Cross(const Vect<3,T>& v1, const Vect<3,T>& v2)
{
	return Vect<3,T>(
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
		);
}

template <class T> inline Vect<3,T> Dehomogenize(const Vect<4,T>& v)
{
	T w_1 = T(1.0) / v.w;
	return Vect<3,T>(v.x * w_1, v.y * w_1, v.z * w_1);
}

template <class T> inline T Volume (const Vect<3,T>& v)
{
	return v.x * v.y * v.z;
}

template <class T> inline Vect<3, T> Lerp(const T& f, const Vect<3, T>& a0, const Vect<3, T>& a1)
{
	return Vect<3, T>(
		(1 - f)*a0.x + f*a1.x,
		(1 - f)*a0.y + f*a1.y,
		(1 - f)*a0.z + f*a1.z
		);
}

template <class T> inline Vect<3, int> Signum(const Vect<3, T>& v) {
	return Vect<3, int>(
		(T(0) < v.x) - (v.x < T(0)),
		(T(0) < v.y) - (v.y < T(0)),
		(T(0) < v.z) - (v.z < T(0))
		);
}


template <class T>
class Vect<4,T>
{
public:

	T x, y, z, w;

	Vect() { }
	Vect(const Vect<4,T>& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
	explicit Vect(const T& s) : x(s), y(s), z(s), w(s) { }
	Vect(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) { }
	Vect(const Vect<3,T>& v, const T& w) : x(v.x), y(v.y), z(v.z), w(w) { }
	explicit Vect(const T* p) : x(p[0]), y(p[1]), z(p[2]), w(p[3]) { }
	template <int M, class S> explicit Vect(const Vect<M,S>& v) : x(T(v[0])), y(T(v[1])), z(T(v[2])), w(T(v[3])) { }
	template <int M, class S> Vect(const Vect<M,S>& v, const T& s)
	{
		int M_ = M < 4 ? M : 4;
		for (int i = 0; i < M_; i++) { (&x)[i] = T(v[i]); }
		for (int i = M_; i < 4; i++) { (&x)[i] = s; }
	}

	T& operator[](int i) { return (&x)[i]; }
	const T& operator[](int i) const { return (&x)[i]; }

	void Clear() { x = T(0); y = T(0); z = T(0); w = T(0); }

	Vect<4,T>& operator=(const Vect<4,T>& v) { x = v.x; y = v.y; z = v.z; w = v.w; return *this; }

	Vect<4,T>& operator+=(const Vect<4,T>& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }
	Vect<4,T>& operator-=(const Vect<4,T>& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }
	Vect<4,T>& operator*=(const T& s) { x *= s; y *= s; z *= s; w *= s; return *this; }
	Vect<4,T>& operator*=(const Vect<4,T>& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }
	Vect<4,T>& operator/=(const T& s) { x /= s; y /= s; z /= s; w /= s; return *this; }
	Vect<4,T>& operator/=(const Vect<4,T>& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }
	Vect<4,T>& operator%=(const T& s) { x %= s; y %= s; z %= s; w %= s; return *this; }
	Vect<4,T>& operator%=(const Vect<4,T>& v) { x %= v.x; y %= v.y; z %= v.z; w %= v.w; return *this; }
	Vect<4,T>& operator<<=(int n) { x <<= n; y <<= n; z <<= n; w <<= n; return *this; }
	Vect<4,T>& operator>>=(int n) { x >>= n; y >>= n; z >>= n; w >>= n; return *this; }
	Vect<4,T>& operator&=(const T& s) { x &= s; y &= s; z &= s; w &= s; return *this; }
	Vect<4,T>& operator&=(const Vect<4,T>& v) { x &= v.x; y &= v.y; z &= v.z; w &= v.w; return *this; }
	Vect<4,T>& operator|=(const T& s) { x |= s; y |= s; z |= s; w |= s; return *this; }
	Vect<4,T>& operator|=(const Vect<4,T>& v) { x |= v.x; y |= v.y; z |= v.z; w |= v.w; return *this; }
	Vect<4,T>& operator^=(const T& s) { x ^= s; y ^= s; z ^= s; w ^= s; return *this; }
	Vect<4,T>& operator^=(const Vect<4,T>& v) { x ^= v.x; y ^= v.y; z ^= v.z; w ^= v.w; return *this; }

	operator T*() { return &x; } // Cast to T*
	operator const T*() const { return &x; } // Cast to const T*

	T MinElem() const { T res = x; if (y < res) res = y; if (z < res) res = z; if (w < res) res = w; return res; }
	T MaxElem() const { T res = x; if (res < y) res = y; if (res < z) res = z; if (res < w) res = w; return res; }

	Vect<3,T> xyz() const { return Vect<3,T>(x, y, z); }

	template <class Archive>
	void serialize(Archive & ar, const unsigned int version) { ar & x; ar & y; ar & z; ar & w; }
};

template <class T> inline Vect<4,T> operator+(const Vect<4,T>& v) { return v; }
template <class T> inline Vect<4,T> operator+(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w); }
template <class T> inline Vect<4,T> operator-(const Vect<4,T>& v) { return Vect<4,T>(-v.x, -v.y, -v.z, -v.w); }
template <class T> inline Vect<4,T> operator-(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w); }
template <class T> inline Vect<4,T> operator*(const T& s, const Vect<4,T>& v) { return Vect<4,T>(s * v.x, s * v.y, s * v.z, s * v.w); }
template <class T> inline Vect<4,T> operator*(const Vect<4,T>& v, const T& s) { return Vect<4,T>(v.x * s, v.y * s, v.z * s, v.w * s); }
template <class T> inline Vect<4,T> operator*(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w); }
template <class T> inline Vect<4,T> operator/(const T& s, const Vect<4,T>& v) { return Vect<4,T>(s / v.x, s / v.y, s / v.z, s / v.w); }
template <class T> inline Vect<4,T> operator/(const Vect<4,T>& v, const T& s) { return Vect<4,T>(v.x / s, v.y / s, v.z / s, v.w / s); }
template <class T> inline Vect<4,T> operator/(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w); }
template <class T> inline Vect<4,T> operator%(const Vect<4,T>& v, const T& s) { return Vect<4,T>(v.x % s, v.y % s, v.z % s, v.w % s); }
template <class T> inline Vect<4,T> operator%(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x % v2.x, v1.y % v2.y, v1.z % v2.z, v1.w % v2.w); }
template <class T> inline Vect<4,T> operator<<(const Vect<4,T>& v, int n) { return Vect<4,T>(v.x << n, v.y << n, v.z << n, v.w << n); }
template <class T> inline Vect<4,T> operator>>(const Vect<4,T>& v, int n) { return Vect<4,T>(v.x >> n, v.y >> n, v.z >> n, v.w >> n); }
template <class T> inline Vect<4,T> operator&(const Vect<4,T>& v, const T& s) { return Vect<4,T>(v.x & s, v.y & s, v.z & s, v.w & s); }
template <class T> inline Vect<4,T> operator&(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x & v2.x, v1.y & v2.y, v1.z & v2.z, v1.w & v2.w); }
template <class T> inline Vect<4,T> operator|(const Vect<4,T>& v, const T& s) { return Vect<4,T>(v.x | s, v.y | s, v.z | s, v.w | s); }
template <class T> inline Vect<4,T> operator|(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x | v2.x, v1.y | v2.y, v1.z | v2.z, v1.w & v2.w); }
template <class T> inline Vect<4,T> operator^(const Vect<4,T>& v, const T& s) { return Vect<4,T>(v.x ^ s, v.y ^ s, v.z ^ s, v.w ^ s); }
template <class T> inline Vect<4,T> operator^(const Vect<4,T>& v1, const Vect<4,T>& v2) { return Vect<4,T>(v1.x ^ v2.x, v1.y ^ v2.y, v1.z ^ v2.z, v1.w ^ v2.w); }
template <class T> inline Vect<4,T> abs(const Vect<4,T>& v) { return Vect<4,T>(std::abs(v.x), std::abs(v.y), std::abs(v.z), std::abs(v.w)); }

template <class T> inline bool operator==(const Vect<4,T>& v1, const Vect<4,T>& v2) { return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w; }
template <class T> inline bool operator!=(const Vect<4,T>& v1, const Vect<4,T>& v2) { return v1.x != v2.x || v1.y != v2.y || v1.z != v2.z || v1.w != v2.w; }
template <class T> inline bool operator<(const Vect<4,T>& v1, const Vect<4,T>& v2) { return v1.x < v2.x && v1.y < v2.y && v1.z < v2.z && v1.w < v2.w; }
template <class T> inline bool operator<=(const Vect<4,T>& v1, const Vect<4,T>& v2) { return v1.x <= v2.x && v1.y <= v2.y && v1.z <= v2.z && v1.w <= v2.w; }
template <class T> inline bool operator>(const Vect<4,T>& v1, const Vect<4,T>& v2) { return v1.x > v2.x && v1.y > v2.y && v1.z > v2.z && v1.w > v2.w; }
template <class T> inline bool operator>=(const Vect<4,T>& v1, const Vect<4,T>& v2) { return v1.x >= v2.x && v1.y >= v2.y && v1.z >= v2.z && v1.w >= v2.w; }

template <class T> inline T Dot(const Vect<4,T>& v1, const Vect<4,T>& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w; }
template <class T> inline T Length(const Vect<4,T>& v) { return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w); }
template <class T> inline T LengthSqr(const Vect<4,T>& v) { return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w; }

template <class T> inline Vect<4,T> Normalize(const Vect<4,T>& v)
{
	T length_1 = T(1.0) / sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	return Vect<4,T>(v.x * length_1, v.y * length_1, v.z * length_1, v.w * length_1);
}

template <class T> inline Vect<4,T> SafeNormalize(const Vect<4,T>& v)
{
	T length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
	if (length != T(0.0))
	{
		T length_1 = T(1.0) / length;
		return Vect<4,T>(v.x * length_1, v.y * length_1, v.z * length_1, v.w * length_1);
	}
	else
	{
		return v;
	}
}

template <class T> inline Vect<4,T> SafeNormalizePlane(const Vect<4,T>& v)
{
	T length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (length != T(0.0))
	{
		T length_1 = T(1.0) / length;
		return Vect<4,T>(v.x * length_1, v.y * length_1, v.z * length_1, v.w * length_1);
	}
	else
	{
		return v;
	}
}

template <class T> inline Vect<4,T> Min(const Vect<4,T>& v1, const Vect<4,T>& v2)
{
	return Vect<4,T>(
		v2.x < v1.x ? v2.x : v1.x,
		v2.y < v1.y ? v2.y : v1.y,
		v2.z < v1.z ? v2.z : v1.z,
		v2.w < v1.w ? v2.w : v1.w
		);
}

template <class T> inline Vect<4,T> Max(const Vect<4,T>& v1, const Vect<4,T>& v2)
{
	return Vect<4,T>(
		v1.x < v2.x ? v2.x : v1.x,
		v1.y < v2.y ? v2.y : v1.y,
		v1.z < v2.z ? v2.z : v1.z,
		v1.w < v2.w ? v2.w : v1.w
		);
}

template <class T> inline Vect<4,T> Floor(const Vect<4,T>& v) { return Vect<4,T>(std::floor(v.x), std::floor(v.y), std::floor(v.z), std::floor(v.w)); }
template <class T> inline Vect<4,T> Ceil(const Vect<4,T>& v) { return Vect<4,T>(std::ceil(v.x), std::ceil(v.y), std::ceil(v.z), std::ceil(v.w)); }

template <class T> inline Vect<4,T> MinClamp(const Vect<4,T>& v, const Vect<4,T>& vMin)
{
	return Vect<4,T>(
		v.x < vMin.x ? vMin.x : v.x,
		v.y < vMin.y ? vMin.y : v.y,
		v.z < vMin.z ? vMin.z : v.z,
		v.w < vMin.w ? vMin.w : v.w
		);
}

template <class T> inline Vect<4,T> MaxClamp(const Vect<4,T>& v, const Vect<4,T>& vMax)
{
	return Vect<4,T>(
		vMax.x < v.x ? vMax.x : v.x,
		vMax.y < v.y ? vMax.y : v.y,
		vMax.z < v.z ? vMax.z : v.z,
		vMax.w < v.w ? vMax.w : v.w
		);
}

template <class T> inline Vect<4,T> Clamp(const Vect<4,T>& v, const Vect<4,T>& vMin, const Vect<4,T>& vMax)
{
	return Vect<4,T>(
		v.x < vMin.x ? vMin.x : (vMax.x < v.x ? vMax.x : v.x),
		v.y < vMin.y ? vMin.y : (vMax.y < v.y ? vMax.y : v.y),
		v.z < vMin.z ? vMin.z : (vMax.z < v.z ? vMax.z : v.z),
		v.w < vMin.w ? vMin.w : (vMax.w < v.w ? vMax.w : v.w)
		);
}

template <class T> inline Vect<4, T> Lerp(const T& f, const Vect<4, T>& a0, const Vect<4, T>& a1)
{
	return Vect<4, T>(
		(1 - f)*a0.x + f*a1.x,
		(1 - f)*a0.y + f*a1.y,
		(1 - f)*a0.z + f*a1.z,
		(1 - f)*a0.w + f*a1.w
		);
}
template <class T> inline Vect<4, T> Lerp3(const Vect<3, T>& f,
	const Vect<4, T>& a000, const Vect<4, T>& a001, const Vect<4, T>& a010, const Vect<4, T>& a011,
	const Vect<4, T>& a100, const Vect<4, T>& a101, const Vect<4, T>& a110, const Vect<4, T>& a111)
{
	return Lerp(f.x,
		Lerp(f.y, Lerp(f.z, a000, a001), Lerp(f.z, a010, a011)),
		Lerp(f.y, Lerp(f.z, a100, a101), Lerp(f.z, a110, a111))
		);
}

template <class T> inline std::ostream& operator<<(std::ostream& ost, const Vect<4,T>& v) { ost << v.x << ' ' << v.y << ' ' << v.z << ' ' << v.w; return ost; }
template <class T> inline std::wostream& operator<<(std::wostream& wost, const Vect<4,T>& v) { wost << v.x << L' ' << v.y << L' ' << v.z << L' ' << v.w; return wost; }
template <class T> inline std::istream& operator>>(std::istream& ist, Vect<4,T>& v) { Vect<4,T> tmp; if (ist >> tmp.x >> tmp.y >> tmp.z >> tmp.w) { v = tmp; } return ist; }
template <class T> inline std::wistream& operator>>(std::wistream& wist, Vect<4,T>& v) { Vect<4,T> tmp; if (wist >> tmp.x >> tmp.y >> tmp.z >> tmp.w) { v = tmp; } return wist; }


template <int N, class T>
class Vect
{
public:

	T elems[N];

	Vect() { }
	Vect(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] = v.elems[i]; }
	}
	explicit Vect(const T& s)
	{
		for (int i = 0; i < N; i++) { elems[i] = s; }
	}
	explicit Vect(const T* p)
	{
		for (int i = 0; i < N; i++) { elems[i] = p[i]; }
	}
	template <int M, class S> explicit Vect(const Vect<M,S>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] = T(v[i]); }
	}
	template <int M, class S> Vect(const Vect<M,S>& v, const T& s)
	{
		int M_ = M < N ? M : N;
		for (int i = 0; i < M_; i++) { elems[i] = T(v[i]); }
		for (int i = M_; i < N; i++) { elems[i] = s; }
	}

	T& operator[](int i) { return elems[i]; }
	const T& operator[](int i) const { return elems[i]; }

	void Clear()
	{
		for (int i = 0; i < N; i++) { elems[i] = T(0); }
	}

	Vect<N,T>& operator=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] = v.elems[i]; }
		return *this;
	}

	Vect<N,T>& operator+=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] += v.elems[i]; }
		return *this;
	}
	Vect<N,T>& operator-=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] -= v.elems[i]; }
		return *this;
	}
	Vect<N,T>& operator*=(const T& s)
	{
		for (int i = 0; i < N; i++) { elems[i] *= s; }
		return *this;
	}
	Vect<N,T>& operator*=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] *= v.elems[i]; }
		return *this;
	}
	Vect<N,T>& operator/=(const T& s)
	{
		for (int i = 0; i < N; i++) { elems[i] /= s; }
		return *this;
	}
	Vect<N,T>& operator/=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] /= v.elems[i]; }
		return *this;
	}
	Vect<N,T>& operator%=(const T& s)
	{
		for (int i = 0; i < N; i++) { elems[i] %= s; }
		return *this;
	}
	Vect<N,T>& operator%=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] %= v.elems[i]; }
		return *this;
	}
	Vect<N,T>& operator<<=(int n)
	{
		for (int i = 0; i < N; i++) { elems[i] <<= n; }
		return *this;
	}
	Vect<N,T>& operator>>=(int n)
	{
		for (int i = 0; i < N; i++) { elems[i] >>= n; }
		return *this;
	}
	Vect<N,T>& operator&=(const T& s)
	{
		for (int i = 0; i < N; i++) { elems[i] &= s; }
		return *this;
	}
	Vect<N,T>& operator&=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] &= v.elems[i]; }
		return *this;
	}
	Vect<N,T>& operator|=(const T& s)
	{
		for (int i = 0; i < N; i++) { elems[i] |= s; }
		return *this;
	}
	Vect<N,T>& operator|=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] |= v.elems[i]; }
		return *this;
	}
	Vect<N,T>& operator^=(const T& s)
	{
		for (int i = 0; i < N; i++) { elems[i] ^= s; }
		return *this;
	}
	Vect<N,T>& operator^=(const Vect<N,T>& v)
	{
		for (int i = 0; i < N; i++) { elems[i] ^= v.elems[i]; }
		return *this;
	}

	operator T*() { return elems; } // Cast to T*
	operator const T*() const { return elems; } // Cast to const T*

	T MinElem() const
	{
		T res = elems[0];
		for (int i = 1; i < N; i++) { if (elems[i] < res) res = elems[i]; }
		return res;
	}
	T MaxElem() const
	{
		T res = elems[0];
		for (int i = 1; i < N; i++) { if (res < elems[i]) res = elems[i]; }
		return res;
	}
};

template <int N, class T> inline Vect<N,T> operator+(const Vect<N,T>& v) { return v; }
template <int N, class T> inline Vect<N,T> operator+(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] + v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator-(const Vect<N,T>& v)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = -v.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator-(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] - v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator*(const T& s, const Vect<N,T>& v)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = s * v.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator*(const Vect<N,T>& v, const T& s)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] * s; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator*(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] * v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator/(const T& s, const Vect<N,T>& v)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = s / v.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator/(const Vect<N,T>& v, const T& s)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] / s; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator/(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] / v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator%(const Vect<N,T>& v, const T& s)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] % s; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator%(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] % v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator<<(const Vect<N,T>& v, int n)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] << n; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator>>(const Vect<N,T>& v, int n)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] >> n; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator&(const Vect<N,T>& v, const T& s)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] & s; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator&(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] & v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator|(const Vect<N,T>& v, const T& s)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] | s; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator|(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] | v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator^(const Vect<N,T>& v, const T& s)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] ^ s; }
	return res;
}
template <int N, class T> inline Vect<N,T> operator^(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v1.elems[i] ^ v2.elems[i]; }
	return res;
}
template <int N, class T> inline Vect<N,T> abs(const Vect<N,T>& v)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = std::abs(v.elems[i]); }
	return res;
}

template <int N, class T> inline bool operator==(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	bool res = (v1.elems[0] == v2.elems[0]);
	for (int i = 1; i < N; i++) { res = res && (v1.elems[i] == v2.elems[i]); }
	return res;
}
template <int N, class T> inline bool operator!=(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	bool res = (v1.elems[0] != v2.elems[0]);
	for (int i = 1; i < N; i++) { res = res || (v1.elems[i] != v2.elems[i]); }
	return res;
}
template <int N, class T> inline bool operator<(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	bool res = (v1.elems[0] < v2.elems[0]);
	for (int i = 1; i < N; i++) { res = res && (v1.elems[i] < v2.elems[i]); }
	return res;
}
template <int N, class T> inline bool operator<=(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	bool res = (v1.elems[0] <= v2.elems[0]);
	for (int i = 1; i < N; i++) { res = res && (v1.elems[i] <= v2.elems[i]); }
	return res;
}
template <int N, class T> inline bool operator>(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	bool res = (v1.elems[0] > v2.elems[0]);
	for (int i = 1; i < N; i++) { res = res && (v1.elems[i] > v2.elems[i]); }
	return res;
}
template <int N, class T> inline bool operator>=(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	bool res = (v1.elems[0] >= v2.elems[0]);
	for (int i = 1; i < N; i++) { res = res && (v1.elems[i] >= v2.elems[i]); }
	return res;
}

template <int N, class T> inline T Dot(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	T res = v1.elems[0] * v2.elems[0];
	for (int i = 1; i < N; i++) { res += v1.elems[i] * v2.elems[i]; }
	return res;
}
template <int N, class T> inline T Length(const Vect<N,T>& v)
{
	T res = v.elems[0] * v.elems[0];
	for (int i = 1; i < N; i++) { res += v.elems[i] * v.elems[i]; }
	return sqrt(res);
}
template <int N, class T> inline T LengthSqr(const Vect<N,T>& v)
{
	T res = v.elems[0] * v.elems[0];
	for (int i = 1; i < N; i++) { res += v.elems[i] * v.elems[i]; }
	return res;
}

template <int N, class T> inline Vect<N,T> Normalize(const Vect<N,T>& v)
{
	T lengthSqr = v.elems[0] * v.elems[0];
	for (int i = 1; i < N; i++) { lengthSqr += v.elems[i] * v.elems[i]; }
	T length = sqrt(lengthSqr);
	T length_1 = T(1.0) / length;
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] * length_1; }
	return res;
}

template <int N, class T> inline Vect<N,T> SafeNormalize(const Vect<N,T>& v)
{
	T lengthSqr = v.elems[0] * v.elems[0];
	for (int i = 1; i < N; i++) { lengthSqr += v.elems[i] * v.elems[i]; }
	T length = sqrt(lengthSqr);
	if (length != T(0.0))
	{
		T length_1 = T(1.0) / length;
		Vect<N,T> res;
		for (int i = 0; i < N; i++) { res.elems[i] = v.elems[i] * length_1; }
		return res;
	}
	else
	{
		return v;
	}
}

template <int N, class T> inline Vect<N,T> Min(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = (v2.elems[i] < v1.elems[i] ? v2.elems[i] : v1.elems[i]); }
	return res;
}

template <int N, class T> inline Vect<N,T> Max(const Vect<N,T>& v1, const Vect<N,T>& v2)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = (v1.elems[i] < v2.elems[i] ? v2.elems[i] : v1.elems[i]); }
	return res;
}

template <int N, class T> inline Vect<N,T> Floor(const Vect<N,T>& v)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = std::floor(v.elems[i]); }
	return res;
}
template <int N, class T> inline Vect<N,T> Ceil(const Vect<N,T>& v)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = std::ceil(v.elems[i]); }
	return res;
}

template <int N, class T> inline Vect<N,T> MinClamp(const Vect<N,T>& v, const Vect<N,T>& vMin)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = (v.elems[i] < vMin.elems[i] ? vMin.elems[i] : v.elems[i]); }
	return res;
}

template <int N, class T> inline Vect<N,T> MaxClamp(const Vect<N,T>& v, const Vect<N,T>& vMax)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = (vMax.elems[i] < v.elems[i] ? vMax.elems[i] : v.elems[i]); }
	return res;
}

template <int N, class T> inline Vect<N,T> Clamp(const Vect<N,T>& v, const Vect<N,T>& vMin, const Vect<N,T>& vMax)
{
	Vect<N,T> res;
	for (int i = 0; i < N; i++) { res.elems[i] = (v.elems[i] < vMin.elems[i] ? vMin.elems[i] : (vMax.elems[i] < v.elems[i] ? vMax.elems[i] : v.elems[i])); }
	return res;
}

template <int N, class T> inline std::ostream& operator<<(std::ostream& ost, const Vect<N,T>& v)
{
	for (int i = 0; i < N-1; i++) { ost << v.elems[i] << ' '; }
	ost << v.elems[N-1];
	return ost;
}
template <int N, class T> inline std::wostream& operator<<(std::wostream& wost, const Vect<N,T>& v)
{
	for (int i = 0; i < N-1; i++) { wost << v.elems[i] << L' '; }
	wost << v.elems[N-1];
	return wost;
}
template <int N, class T> inline std::istream& operator>>(std::istream& ist, Vect<N,T>& v)
{
	Vect<N,T> tmp;
	for (int i = 0; i < N; i++) { ist >> tmp.elems[i]; }
	if (ist) { v = tmp; }
	return ist;
}
template <int N, class T> inline std::wistream& operator>>(std::wistream& wist, Vect<N,T>& v)
{
	Vect<N,T> tmp;
	for (int i = 0; i < N; i++) { wist >> tmp.elems[i]; }
	if (wist) { v = tmp; }
	return wist;
}


typedef Vect<1,int> Vect1i;
typedef Vect<2,int> Vect2i;
typedef Vect<3,int> Vect3i;
typedef Vect<4,int> Vect4i;
typedef Vect<1,unsigned int> Vect1ui;
typedef Vect<2,unsigned int> Vect2ui;
typedef Vect<3,unsigned int> Vect3ui;
typedef Vect<4,unsigned int> Vect4ui;
typedef Vect<1,float> Vect1f;
typedef Vect<2,float> Vect2f;
typedef Vect<3,float> Vect3f;
typedef Vect<4,float> Vect4f;
typedef Vect<1,double> Vect1d;
typedef Vect<2,double> Vect2d;
typedef Vect<3,double> Vect3d;
typedef Vect<4,double> Vect4d;
typedef Vect<1,bool> Vect1b;
typedef Vect<2,bool> Vect2b;
typedef Vect<3,bool> Vect3b;
typedef Vect<4,bool> Vect4b;


template <class T>
class Box
{
public:
	Vect<3,T>		m_vCenter;
	Vect<3,T>		m_vHalfExtent;
};



template <int N, class T>
struct VectComp;


template <class T>
struct VectComp<1,T> : public std::binary_function<Vect<1,T>, Vect<1,T>, bool>
{
	bool operator()(const Vect<1,T>& v1, const Vect<1,T>& v2) const
	{
		return v1.x < v2.x;
	}
};


template <class T>
struct VectComp<2,T> : public std::binary_function<Vect<2,T>, Vect<2,T>, bool>
{
	bool operator()(const Vect<2,T>& v1, const Vect<2,T>& v2) const
	{
		if (v1.x != v2.x) { return v1.x < v2.x; }
		return v1.y < v2.y;
	}
};


template <class T>
struct VectComp<3,T> : public std::binary_function<Vect<3,T>, Vect<3,T>, bool>
{
	bool operator()(const Vect<3,T>& v1, const Vect<3,T>& v2) const
	{
		if (v1.x != v2.x) { return v1.x < v2.x; }
		if (v1.y != v2.y) { return v1.y < v2.y; }
		return v1.z < v2.z;
	}
};


template <class T>
struct VectComp<4,T> : public std::binary_function<Vect<4,T>, Vect<4,T>, bool>
{
	bool operator()(const Vect<4,T>& v1, const Vect<4,T>& v2) const
	{
		if (v1.x != v2.x) { return v1.x < v2.x; }
		if (v1.y != v2.y) { return v1.y < v2.y; }
		if (v1.z != v2.z) { return v1.z < v2.z; }
		return v1.w < v2.w;
	}
};


template <int N, class T>
struct VectComp : public std::binary_function<Vect<N,T>, Vect<N,T>, bool>
{
	bool operator()(const Vect<N,T>& v1, const Vect<N,T>& v2) const
	{
		for (int i = 0; i < N-1; i++)
		{
			if (v1.elems[i] != v2.elems[i]) { return v1.elems[i] < v2.elems[i]; }
		}
		return v1.elems[N-1] < v2.elems[N-1];
	}
};


typedef VectComp<1,int> VectComp1i;
typedef VectComp<2,int> VectComp2i;
typedef VectComp<3,int> VectComp3i;
typedef VectComp<4,int> VectComp4i;
typedef VectComp<1,unsigned int> VectComp1ui;
typedef VectComp<2,unsigned int> VectComp2ui;
typedef VectComp<3,unsigned int> VectComp3ui;
typedef VectComp<4,unsigned int> VectComp4ui;
typedef VectComp<1,float> VectComp1f;
typedef VectComp<2,float> VectComp2f;
typedef VectComp<3,float> VectComp3f;
typedef VectComp<4,float> VectComp4f;
typedef VectComp<1,double> VectComp1d;
typedef VectComp<2,double> VectComp2d;
typedef VectComp<3,double> VectComp3d;
typedef VectComp<4,double> VectComp4d;


template <int N, class T>
struct VectCompDesc;


template <class T>
struct VectCompDesc<1,T> : public std::binary_function<Vect<1,T>, Vect<1,T>, bool>
{
	bool operator()(const Vect<1,T>& v1, const Vect<1,T>& v2) const
	{
		return v2.x < v1.x;
	}
};


template <class T>
struct VectCompDesc<2,T> : public std::binary_function<Vect<2,T>, Vect<2,T>, bool>
{
	bool operator()(const Vect<2,T>& v1, const Vect<2,T>& v2) const
	{
		if (v1.x != v2.x) { return v2.x < v1.x; }
		return v2.y < v1.y;
	}
};


template <class T>
struct VectCompDesc<3,T> : public std::binary_function<Vect<3,T>, Vect<3,T>, bool>
{
	bool operator()(const Vect<3,T>& v1, const Vect<3,T>& v2) const
	{
		if (v1.x != v2.x) { return v2.x < v1.x; }
		if (v1.y != v2.y) { return v2.y < v1.y; }
		return v2.z < v1.z;
	}
};


template <class T>
struct VectCompDesc<4,T> : public std::binary_function<Vect<4,T>, Vect<4,T>, bool>
{
	bool operator()(const Vect<4,T>& v1, const Vect<4,T>& v2) const
	{
		if (v1.x != v2.x) { return v2.x < v1.x; }
		if (v1.y != v2.y) { return v2.y < v1.y; }
		if (v1.z != v2.z) { return v2.z < v1.z; }
		return v2.w < v1.w;
	}
};


template <int N, class T>
struct VectCompDesc : public std::binary_function<Vect<N,T>, Vect<N,T>, bool>
{
	bool operator()(const Vect<N,T>& v1, const Vect<N,T>& v2) const
	{
		for (int i = 0; i < N-1; i++)
		{
			if (v1.elems[i] != v2.elems[i]) { return v2.elems[i] < v1.elems[i]; }
		}
		return v2.elems[N-1] < v1.elems[N-1];
	}
};


typedef VectCompDesc<1,int> VectCompDesc1i;
typedef VectCompDesc<2,int> VectCompDesc2i;
typedef VectCompDesc<3,int> VectCompDesc3i;
typedef VectCompDesc<4,int> VectCompDesc4i;
typedef VectCompDesc<1,unsigned int> VectCompDesc1ui;
typedef VectCompDesc<2,unsigned int> VectCompDesc2ui;
typedef VectCompDesc<3,unsigned int> VectCompDesc3ui;
typedef VectCompDesc<4,unsigned int> VectCompDesc4ui;
typedef VectCompDesc<1,float> VectCompDesc1f;
typedef VectCompDesc<2,float> VectCompDesc2f;
typedef VectCompDesc<3,float> VectCompDesc3f;
typedef VectCompDesc<4,float> VectCompDesc4f;
typedef VectCompDesc<1,double> VectCompDesc1d;
typedef VectCompDesc<2,double> VectCompDesc2d;
typedef VectCompDesc<3,double> VectCompDesc3d;
typedef VectCompDesc<4,double> VectCompDesc4d;

#ifndef FOR3
#define FOR3(vi, vi0, vi1) \
	for ((vi)##.z = (vi0)##.z; (vi)##.z < (vi1)##.z; ++(vi)##.z)\
		for ((vi)##.y = (vi0)##.y; (vi)##.y < (vi1)##.y; ++(vi)##.y)\
			for ((vi)##.x = (vi0)##.x; (vi)##.x < (vi1)##.x; ++(vi)##.x)
#endif

#ifndef FOR3S
#define FOR3S(vi, vi0, vi1, step) \
	for ((vi)##.z = (vi0)##.z; (vi)##.z < (vi1)##.z; (vi)##.z += step)\
		for ((vi)##.y = (vi0)##.y; (vi)##.y < (vi1)##.y; (vi)##.y += step)\
			for ((vi)##.x = (vi0)##.x; (vi)##.x < (vi1)##.x; (vi)##.x += step)
#endif

class VectN
{
public:
	double x;
};



#endif