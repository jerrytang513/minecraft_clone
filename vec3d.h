#ifndef VEC3D_H_
#define VEC3D_H_
#include <iostream>
#include <math.h>

class Vec3D {
public:
	float x;
	float y;
	float z;

	Vec3D() = default;
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
