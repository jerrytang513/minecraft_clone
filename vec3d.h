#ifndef VEC3D_H_
#define VEC3D_H_
#include <iostream>
#include <math.h>



class Vec3D {
public:

	union{
		struct Coordinate{
			float x;
			float y;
			float z;
		} coord;
		float values[3];
	};

	Vec3D();
	Vec3D(float x, float y, float z);

	float magnitude();
	Vec3D normalize();

	// Some arithemetic operations

	friend Vec3D operator+(const Vec3D& vec, const Vec3D& other);
	friend Vec3D operator-(const Vec3D& vec, const Vec3D& other);
	friend Vec3D operator*(const Vec3D& vec, const Vec3D& other);
	friend Vec3D operator/(const Vec3D& vec, const Vec3D& other);

	friend Vec3D operator+(const Vec3D& vec, const float& val);
	friend Vec3D operator-(const Vec3D& vec, const float& val);
  friend Vec3D operator*(const Vec3D& vec, const float& val);
	friend Vec3D operator/(const Vec3D& vec, const float& val);

	friend Vec3D operator+(const float& val, const Vec3D& vec);
	friend Vec3D operator-(const float& val, const Vec3D& vec);
	friend Vec3D operator*(const float& val, const Vec3D& vec);
  friend Vec3D operator/(const float& val, const Vec3D& vec);

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
