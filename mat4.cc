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

void Mat4::transpose(){
	for(int row = 0; row < 4; row++){
		for(int col = row + 1; col < 4; col++){
			std::swap(matrix[row][col], matrix[col][row]);
		}
	}
}

void Mat4::inverseMat(){
	float inverse[16];
	float det;
	inverse[0] = values[5]  * values[10] * values[15] -
					values[5]  * values[11] * values[14] -
					values[9]  * values[6]  * values[15] +
					values[9]  * values[7]  * values[14] +
					values[13] * values[6]  * values[11] -
					values[13] * values[7]  * values[10];

 inverse[4] = -values[4]  * values[10] * values[15] +
					 values[4]  * values[11] * values[14] +
					 values[8]  * values[6]  * values[15] -
					 values[8]  * values[7]  * values[14] -
					 values[12] * values[6]  * values[11] +
					 values[12] * values[7]  * values[10];

 inverse[8] = values[4]  * values[9] * values[15] -
					values[4]  * values[11] * values[13] -
					values[8]  * values[5] * values[15] +
					values[8]  * values[7] * values[13] +
					values[12] * values[5] * values[11] -
					values[12] * values[7] * values[9];

 inverse[12] = -values[4]  * values[9] * values[14] +
						values[4]  * values[10] * values[13] +
						values[8]  * values[5] * values[14] -
						values[8]  * values[6] * values[13] -
						values[12] * values[5] * values[10] +
						values[12] * values[6] * values[9];

 inverse[1] = -values[1]  * values[10] * values[15] +
					 values[1]  * values[11] * values[14] +
					 values[9]  * values[2] * values[15] -
					 values[9]  * values[3] * values[14] -
					 values[13] * values[2] * values[11] +
					 values[13] * values[3] * values[10];

 inverse[5] = values[0]  * values[10] * values[15] -
					values[0]  * values[11] * values[14] -
					values[8]  * values[2] * values[15] +
					values[8]  * values[3] * values[14] +
					values[12] * values[2] * values[11] -
					values[12] * values[3] * values[10];

 inverse[9] = -values[0]  * values[9] * values[15] +
					 values[0]  * values[11] * values[13] +
					 values[8]  * values[1] * values[15] -
					 values[8]  * values[3] * values[13] -
					 values[12] * values[1] * values[11] +
					 values[12] * values[3] * values[9];

 inverse[13] = values[0]  * values[9] * values[14] -
					 values[0]  * values[10] * values[13] -
					 values[8]  * values[1] * values[14] +
					 values[8]  * values[2] * values[13] +
					 values[12] * values[1] * values[10] -
					 values[12] * values[2] * values[9];

 inverse[2] = values[1]  * values[6] * values[15] -
					values[1]  * values[7] * values[14] -
					values[5]  * values[2] * values[15] +
					values[5]  * values[3] * values[14] +
					values[13] * values[2] * values[7] -
					values[13] * values[3] * values[6];

 inverse[6] = -values[0]  * values[6] * values[15] +
					 values[0]  * values[7] * values[14] +
					 values[4]  * values[2] * values[15] -
					 values[4]  * values[3] * values[14] -
					 values[12] * values[2] * values[7] +
					 values[12] * values[3] * values[6];

 inverse[10] = values[0]  * values[5] * values[15] -
					 values[0]  * values[7] * values[13] -
					 values[4]  * values[1] * values[15] +
					 values[4]  * values[3] * values[13] +
					 values[12] * values[1] * values[7] -
					 values[12] * values[3] * values[5];

 inverse[14] = -values[0]  * values[5] * values[14] +
						values[0]  * values[6] * values[13] +
						values[4]  * values[1] * values[14] -
						values[4]  * values[2] * values[13] -
						values[12] * values[1] * values[6] +
						values[12] * values[2] * values[5];

 inverse[3] = -values[1] * values[6] * values[11] +
					 values[1] * values[7] * values[10] +
					 values[5] * values[2] * values[11] -
					 values[5] * values[3] * values[10] -
					 values[9] * values[2] * values[7] +
					 values[9] * values[3] * values[6];

 inverse[7] = values[0] * values[6] * values[11] -
					values[0] * values[7] * values[10] -
					values[4] * values[2] * values[11] +
					values[4] * values[3] * values[10] +
					values[8] * values[2] * values[7] -
					values[8] * values[3] * values[6];

 inverse[11] = -values[0] * values[5] * values[11] +
						values[0] * values[7] * values[9] +
						values[4] * values[1] * values[11] -
						values[4] * values[3] * values[9] -
						values[8] * values[1] * values[7] +
						values[8] * values[3] * values[5];

 inverse[15] = values[0] * values[5] * values[10] -
					 values[0] * values[6] * values[9] -
					 values[4] * values[1] * values[10] +
					 values[4] * values[2] * values[9] +
					 values[8] * values[1] * values[6] -
					 values[8] * values[2] * values[5];

 det = values[0] * inverse[0] + values[1] * inverse[4] + values[2] * inverse[8] + values[3] * inverse[12];

 det = 1.0 / det;
 for (int i = 0; i < 16; i++)
		 values[i] = inverse[i] * det;
}

Mat4 Mat4::getTranspose(Mat4& mat){
	Mat4 result(mat);
	result.transpose();
	return result;
}

Mat4 Mat4::getInverse(Mat4& mat){
	Mat4 result(mat);
	result.inverseMat();
	return result;
}
/*
Mat3 Mat4::getTopLeft3x3Mat(Mat4& mat){
	float result[9];
	int count = 0;
	for(int i = 0; i < 12; i++){
		if((i+1) % 4 != 0)
			result[count++] = mat.values[i];
	}
	return Mat3(result);
}
*/
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


	std::cout << camera.getFront().coord.x << std::endl;

	view.values[0] = right.coord.x;
	view.values[4] = right.coord.y;
	view.values[8] = right.coord.z;

	view.values[1] = up.coord.x;
	view.values[5] = up.coord.y;
	view.values[9] = up.coord.z;

	view.values[2] = direction.coord.x;
	view.values[6] = direction.coord.y;
	view.values[10] = direction.coord.z;

	pos.values[3] = - position.coord.x;
	pos.values[7] = - position.coord.y;
	pos.values[11] = - position.coord.z;

	view *= pos;
	view.transpose();
	return view;

}

void Mat4::multiply(Mat4& other) {
	float result[16];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0.0f;
			for (int k = 0; k < 4; k++) {
				sum +=  other.values[j + k * 4] *values[k + i * 4];
			}
			result[j + i * 4] = sum;
		}
	}

	for(int i = 0; i < 16; i++){
		values[i] = result[i];
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
