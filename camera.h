#ifndef CAMERA_H_
#define CAMERA_H_
#include "vec3d.h"

enum class Movement{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

// Default values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
	Vec3D front;
	Vec3D position;
	Vec3D target;
	Vec3D direction;
	Vec3D right;
	Vec3D up;
	Vec3D worldUp;

	float yaw;
	float pitch;
	float zoom;

	void update();

public:
	Camera(Vec3D position, Vec3D target, Vec3D worldUp);
	void setPosition(Vec3D position);

	Vec3D getPosition();
	Vec3D getDirection();
	Vec3D getRight();
	Vec3D getUp();
	Vec3D getFront();

	float getZoom();

	void processKeyboard(Movement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseScroll(float yoffset);

};

#endif
