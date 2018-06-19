#ifndef MAT3_H_
#define MAT3_H_

#include <vector>
#include "vec3d.h"
class Mat4 {
public:

	union {
		float values[9];
		float matrix[3][3];
		Vec3D cols[3];
	};

	Mat3();
	Mat3(float* values);
	// copy ctr
	Mat3(Mat3& mat);

	void setDiagonal(float* values);
	void multiply(Mat3& mat);
	void transpose();
	void inverse();

	friend Mat3 operator*(Mat3& left, Mat3& right);
	void operator*=(Mat3& other);
};

#endif
