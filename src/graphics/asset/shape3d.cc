#include "shape3d.h"

Shape3D::Shape3D(Vec3D vec):center{vec},xAxis{Vec3D(1,0,0)},yAxis{Vec3D(0,1,0)},zAxis{Vec3D(0,0,1)}{}
Shape3D::Shape3D(Vec3D vec,Vec3D xAxis,Vec3D yAxis,Vec3D zAxis):center{vec},xAxis{xAxis},yAxis{yAxis},zAxis{zAxis}{}

void Shape3D::setXAxis(Vec3D xAxis){
        this->xAxis= xAxis;
}

void Shape3D::setYAxis(Vec3D yAxis){
        this->yAxis = yAxis;
}

void Shape3D::setZAxis(Vec3D zAxis){
        this->zAxis = zAxis;
}

Vec3D Shape3D::getXAxis(){
        return this->xAxis;
}

Vec3D Shape3D::getYAxis(){
        return this->yAxis;
}

Vec3D Shape3D::getZAxis(){
        return this->zAxis;
}
