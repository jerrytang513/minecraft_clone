#ifndef Vec2D_H_
#define Vec2D_H_
#include <iostream>
#include <math.h>



class Vec2D {
public:

	union{
		struct Coordinate{
			float x;
			float y;
		} coord;
		float values[2];
	};

	Vec2D();
	Vec2D(float x, float y);

	float magnitude();
	Vec2D normalize();

	// Some arithemetic operations

	friend Vec2D operator+(const Vec2D& vec, const Vec2D& other);
	friend Vec2D operator-(const Vec2D& vec, const Vec2D& other);
	friend Vec2D operator*(const Vec2D& vec, const Vec2D& other);
	friend Vec2D operator/(const Vec2D& vec, const Vec2D& other);

	friend Vec2D operator+(const Vec2D& vec, const float& val);
	friend Vec2D operator-(const Vec2D& vec, const float& val);
  friend Vec2D operator*(const Vec2D& vec, const float& val);
	friend Vec2D operator/(const Vec2D& vec, const float& val);

	friend Vec2D operator+(const float& val, const Vec2D& vec);
	friend Vec2D operator-(const float& val, const Vec2D& vec);
	friend Vec2D operator*(const float& val, const Vec2D& vec);
  friend Vec2D operator/(const float& val, const Vec2D& vec);

	void operator+=(const float& val);
	void operator+=(const Vec2D& vec);
	void operator-=(const float& val);
	void operator-=(const Vec2D& vec);
	void operator*=(const float& val);
	void operator*=(const Vec2D& vec);
	void operator/=(const float& val);
	void operator/=(const Vec2D& vec);

	Vec2D dot(const Vec2D& vec);

};
#endif
