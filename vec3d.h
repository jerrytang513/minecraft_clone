#ifndef VEC3D_H_
#define VEC3D_H_
#include <iostream>
#include <math.h>

struct Coordinate{
	Coordinate(float x, float y, float z);
	float x;
	float y;
	float z;
};

class Vec3D {
public:

	union{
		Coordinate coord;
		float* values;
	};

	Vec3D();
	Vec3D(float x, float y, float z);

	float magnitude();
	Vec3D normalize();

	// Some arithemetic operations

	Vec3D operator+(const float& val);
	Vec3D operator+(const Vec3D& vec);
	Vec3D operator-(const float& val);
	Vec3D operator-(const Vec3D& vec);
	Vec3D operator*(const float& val);
	Vec3D operator*(const Vec3D& vec);
	Vec3D operator/(const float& val);
	Vec3D operator/(const Vec3D& vec);

	void operator+=(const float& val);
	void operator+=(const Vec3D& vec);
	void operator-=(const float& val);
	void operator-=(const Vec3D& vec);
	void operator*=(const float& val);
	void operator*=(const Vec3D& vec);
	void operator/=(const float& val);
	void operator/=(const Vec3D& vec);

	Vec3D dot(const Vec3D& vec);
	Vec3D cross(const Vec3D& vec);

};
#endif