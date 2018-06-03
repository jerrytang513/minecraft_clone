#include "mat4.h"
Mat4::Mat4(){
  for(int i = 0; i < 16; i++){
    values[i] = 0.0f;
  }
}

Mat4::Mat4(float* values){
  for(int i = 0; i < 16; i++){
    this->values[i] = values[i];
  }
}

void Mat4::setDiagonal(float* values){
  this->values[0] = values[0];
  this->values[5] = values[1];
  this->values[10] = values[2];
  this->values[15] = values[3];
}

Mat4 Mat4::getIdentity(){
  float f[16] = {1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f,0.0f,0.0f,0.0f,0.0f,1.0f};
  return Mat4(f);
}

Mat4 Mat4::translation(Vec3D& translate){
  Mat4 result = getIdentity();
  result.values[3] = translate.x;
  result.values[7] = translate.y;
  result.values[11] = translate.z;
  return result;
}

Mat4 Mat4::orthographic(float left, float right, float top, float bottom, float near, float far){
  Mat4 result;
  result.values[0] = 2.0f / (right - left);
  result.values[1 + 1 * 4] = 2.0f / (top - bottom);
  result.values[2 + 2 * 4] = 2.0f / (near - far);
  result.values[0 + 3 * 4] = (left + right) / (left - right);
  result.values[1 + 3 * 4] = (bottom + top) / (bottom - top);
  result.values[2 + 3 * 4] = (far + near) / (far - near);
  return result;
}

Mat4 Mat4::perspective(float fov, float aspectRatio, float near, float far){
  Mat4 result;
  float q = 1.0f / (float) tan(toRadians(0.5f * fov));
  float a = q / aspectRatio;
  float b = (near + far) / (near - far);
  float c = (2.0f * near * far) / (near - far);
  result.values[0 + 0 * 4] = a;
  result.values[1 + 1 * 4] = q;
  result.values[2 + 2 * 4] = b;
  result.values[3 + 3 * 4] = -1.0f;
  result.values[2 + 3 * 4] = c;
  return result;
}

Mat4& Mat4::multiply(Mat4& other){
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      float sum = 0.0f;
      for(int k = 0; k < 4; k++){
        sum += values[j + k * 4] * other.values[k + i * 4];
      }
      values[j + i * 4] = sum;
    }
  }
}

Mat4 operator*(Mat4& left, Mat4& right){
  return left.multiply(right);
}

Mat4& Mat4::operator*=(Mat4& other){
  return multiply(other);
}
