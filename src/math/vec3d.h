#include <iostream>

class Vec3D{
	float x;
	float y;
	float z;

	// This placeholder is there to improve the performance of the memory.
	// Since it works better with 4 words than 3 words;
	float placeholder;
	
	Vec3D();
	~Vec3D();
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

	



};
