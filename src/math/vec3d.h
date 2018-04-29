#ifndef VEC3D_H_
#define VEC3D_H_
#include <iostream>
#include <math.h>

class Vec3D{
	// This placeholder is there to improve the performance of the memory.
	// Since it works better with 4 words than 3 words;
	float placeholder;

	public:
	float x;
	float y;
	float z;
	
	Vec3D();
	Vec3D(float x,float y,float z);

	float magnitude();
	Vec3D normalize();


	// Some arithemetic operations
	
	Vec3D operator+(const int val);
	Vec3D operator+(const Vec3D vec);
	Vec3D operator-(const int val);
	Vec3D operator-(const Vec3D vec);
	Vec3D operator*(const int val);
	Vec3D operator*(const Vec3D vec);
	Vec3D operator/(const int val);
	Vec3D operator/(const Vec3D vec);

	void operator+=(const int val);
	void  operator+=(const Vec3D vec);
	void operator-=(const int val);
	void operator-=(const Vec3D vec);
	void operator*=(const int val);
	void operator*=(const Vec3D vec);
	void operator/=(const int val);
	void operator/=(const Vec3D vec);


	



};
#endif
