#include "collision.h"

Collision::Collision(Vec3D centerPos):centerPos{centerPos},xAxis{Vec3D(1,0,0)},yAxis{Vec3D(0,1,0)},zAxis{Vec3D(0,0,1)}{}
Collision::Collision(Vec3D centerPos,Vec3D xAxis,Vec3D yAxis,Vec3D zAxis):centerPos{centerPos},xAxis{xAxis},yAxis{yAxis},zAxis{zAxis}{}

void Collision::setXAxis(Vec3D xAxis){
	this->xAxis= xAxis;
}

void Collision::setYAxis(Vec3D yAxis){
	this->yAxis = yAxis;
}

void Collision::setZAxis(Vec3D zAxis){
	this->zAxis = zAxis;
}

Vec3D Collision::getXAxis(){
	return this->xAxis;
}

Vec3D Collision::getYAxis(){
	return this->yAxis;
}

Vec3D Collision::getZAxis(){
	return this->zAxis;
}

void Collision::setCenterPos(Vec3D centerPos){
	this->centerPos = centerPos;
}

Vec3D Collision::getCenterPos(){
	return this->centerPos;
}
