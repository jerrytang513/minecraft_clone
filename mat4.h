#ifndef MAT4_H_
#define MAT4_H_

#include <vector>
#include "vec4d.h"
#include "vec3d.h"
#include "utilities.h"
#include "quaternion.h"
#include "camera.h"
class Mat4 {
public:

	union {
		float values[16];
		float matrix[4][4];
		Vec4D cols[4];
	};

	Mat4();
	Mat4(float* values);


	void setDiagonal(float* values);
	void multiply(Mat4& mat);
	void transpose();
	void inverseMat();

	friend Mat4 operator*(Mat4& left, Mat4& right);
	void operator*=(Mat4& other);

	static Mat4 getTranspose(Mat4& mat);
	static Mat4 getInverse(Mat4& mat);
	//static Mat3 getTopLeft3x3Mat(Mat4& mat);
	static Mat4 getIdentity();
	static Mat4 translation(Vec3D& translate);
	static Mat4 scale(Vec3D& scale);
	static Mat4 orthographic(float left, float right, float top, float bottom, float near, float far);
	static Mat4 perspective(float fov, float aspectRatio, float near, float far);
	static Mat4 rotation(float angle, Vec3D axis);
	static Mat4 view(Camera& camera);
};

#endif
