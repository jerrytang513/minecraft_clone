#ifndef VEC4D_H_
#define VEC4D_H_
#include <iostream>
#include <math.h>

struct Coordinate4D{
	Coordinate4D(float x, float y, float z, float w);
	float x;
	float y;
	float z;
	float w;
};

class Vec4D {
public:

	union{
		Coordinate4D coord;
		float* values;
	};

	Vec4D();
	Vec4D(float x, float y, float z, float w);

	float magnitude();
	Vec4D normalize();

	// Some arithemetic operations

	friend Vec4D operator+(const Vec4D& vec, const Vec4D& other);
	friend Vec4D operator-(const Vec4D& vec, const Vec4D& other);
	friend Vec4D operator*(const Vec4D& vec, const Vec4D& other);
	friend Vec4D operator/(const Vec4D& vec, const Vec4D& other);

	friend Vec4D operator+(const Vec4D& vec, const float& val);
	friend Vec4D operator-(const Vec4D& vec, const float& val);
  friend Vec4D operator*(const Vec4D& vec, const float& val);
	friend Vec4D operator/(const Vec4D& vec, const float& val);

	friend Vec4D operator+(const float& val, const Vec4D& vec);
	friend Vec4D operator-(const float& val, const Vec4D& vec);
	friend Vec4D operator*(const float& val, const Vec4D& vec);
  friend Vec4D operator/(const float& val, const Vec4D& vec);

	void operator+=(const float& val);
	void operator+=(const Vec4D& vec);
	void operator-=(const float& val);
	void operator-=(const Vec4D& vec);
	void operator*=(const float& val);
	void operator*=(const Vec4D& vec);
	void operator/=(const float& val);
	void operator/=(const Vec4D& vec);

	Vec4D dot(const Vec4D& vec);

};
#endif
