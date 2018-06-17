#include "mat4.h"
Mat4::Mat4() {
	for (int i = 0; i < 16; i++) {
		values[i] = 0.0f;
	}
}

Mat4::Mat4(float* values) {
	for (int i = 0; i < 16; i++) {
		this->values[i] = values[i];
	}
}

void Mat4::setDiagonal(float* values) {
	this->values[0] = values[0];
	this->values[5] = values[1];
	this->values[10] = values[2];
	this->values[15] = values[3];
}

Mat4 Mat4::getIdentity() {
	float f[16] = { 1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f };
	return Mat4(f);
}

Mat4 Mat4::translation(Vec3D& translate) {
	Mat4 result = getIdentity();
	result.values[0 + 4 * 3] = translate.coord.x;
	result.values[1 + 4 * 3] = translate.coord.y;
	result.values[2 + 4 * 3] = translate.coord.z;
	return result;
}

Mat4 Mat4::scale(Vec3D& scale) {
	Mat4 result = getIdentity();
	result.values[0] = scale.coord.x;
	result.values[5] = scale.coord.y;
	result.values[10] = scale.coord.z;
	return result;
}

Mat4 Mat4::orthographic(float left, float right, float top, float bottom, float near, float far) {
	Mat4 result;
	result.values[0] = 2.0f / (right - left);
	result.values[1 + 1 * 4] = 2.0f / (top - bottom);
	result.values[2 + 2 * 4] = 2.0f / (near - far);
	result.values[0 + 3 * 4] = (left + right) / (left - right);
	result.values[1 + 3 * 4] = (bottom + top) / (bottom - top);
	result.values[2 + 3 * 4] = (far + near) / (far - near);
	return result;
}

Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far) {
	Mat4 result;
	float q = 1.0f /((float)aspectRatio * (float)tan(toRadians(0.5f * fov)));
	float a = 1.0f /(float)tan(toRadians(fov));
	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);
	result.values[0 + 0 * 4] = q;
	result.values[1 + 1 * 4] = a;
	result.values[2 + 2 * 4] = b;
	result.values[3 + 2 * 4] = - 1.0f ;
	result.values[2 + 3 * 4] = c;
	return result;
}

Mat4 Mat4::rotation(float angle, Vec3D axis) {
	Mat4 result = getIdentity();
	Quaternion q(angle, axis);
	q.normalize();
	result.values[0] = 2 * (q.x * q.x + q.w * q.w) - 1;
	result.values[1] = 2 * (q.x * q.y + q.z * q.w);
	result.values[2] = 2 * (q.x * q.z - q.y * q.w);
	result.values[3] = 0.0f;
	result.values[4] = 2 * (q.x * q.y - q.z * q.w);
	result.values[5] = 2 * (q.y * q.y + q.w * q.w) - 1;
	result.values[6] = 2 * (q.y * q.z + q.x * q.w);
	result.values[7] = 0.0f;
	result.values[8] = 2 * (q.x * q.z + q.y * q.w);
	result.values[9] = 2 * (q.y * q.z - q.x * q.w);
	result.values[10] = 2 * (q.z * q.z + q.w * q.w) - 1;
	result.values[11] = 0.0f;
	result.values[12] = 0.0f;
	result.values[13] = 0.0f;
	result.values[14] = 0.0f;
	result.values[15] = 1.0f;
	return result;
}

Mat4 Mat4::view(Camera& camera) {
	Mat4 view = getIdentity();
	Mat4 pos = getIdentity();

	Vec3D position = camera.getPosition();
	Vec3D right = camera.getRight();
	Vec3D up = camera.getUp();
	Vec3D direction = camera.getDirection();

	view.values[0] = right.coord.x;
	view.values[1] = up.coord.x;
	view.values[2] = direction.coord.x;

	view.values[4] = right.coord.y;
	view.values[5] = up.coord.y;
	view.values[6] = direction.coord.y;

	view.values[8] = right.coord.z;
	view.values[9] = up.coord.z;
	view.values[10] = direction.coord.z;

	pos.values[3] = -position.coord.x;
	pos.values[7] = -position.coord.y;
	pos.values[11] = -position.coord.z;

	return view * pos;

}

void Mat4::multiply(Mat4& other) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += values[j + k * 4] * other.values[k + i * 4];
			}
			values[j + i * 4] = sum;
		}
	}
}

Mat4 operator*(Mat4& left, Mat4& right) {
	float values[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum += left.values[j + k * 4] * right.values[k + i * 4];
			}
			values[j + i * 4] = sum;
		}
	}
	return Mat4(values);
}

void Mat4::operator*=(Mat4& other) {
	multiply(other);
}
