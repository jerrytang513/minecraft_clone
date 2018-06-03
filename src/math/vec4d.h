#ifndef Vec4D_H_
#define Vec4D_H_
#include <iostream>
#include <math.h>
#include <glm/glm.hpp>

class Vec4D{
	// This placeholder is there to improve the performance of the memory.
	// Since it works better with 4 words than 3 words;
	public:
	float x;
	float y;
	float z;
  float t;

	Vec4D();
	Vec4D(float x,float y,float z,float t);

	glm::vec4 getGLMVec();
	float magnitude();
	Vec4D normalize();

	// Some arithemetic operations

	Vec4D operator+(const float& val);
	Vec4D operator+(const Vec4D& vec);
	Vec4D operator-(const float& val);
	Vec4D operator-(const Vec4D& vec);
	Vec4D operator*(const float& val);
	Vec4D operator*(const Vec4D& vec);
	Vec4D operator/(const float& val);
	Vec4D operator/(const Vec4D& vec);

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
