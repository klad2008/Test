#pragma once

#include <cstdio>
#include <cmath>
#include "objects.h"
#include "const_data.h"

Point3 Point3 :: operator + (Point3 T){
    Point3 X;
    X.x = this -> x + T.x;
    X.y = this -> y + T.y;
    X.z = this -> z + T.z;
    return X;
}

Point3 Point3 :: operator - (Point3 T){
    Point3 X;
    X.x = this -> x - T.x;
    X.y = this -> y - T.y;
    X.z = this -> z - T.z;
    return X;
}

Point3 Point3 :: operator * (double t){
    Point3 X;
    X.x = this -> x * t;
    X.y = this -> y * t;
    X.z = this -> z * t;
    return X;
}


Point3 operator * (int A[3][3], Point3 X){
    Point3 Y;
    int B[3], C[3];
    B[0] = X.x;
    B[1] = X.y;
    B[2] = X.z;
    C[0] = C[1] = C[2] = 0;
    for (int i = 0; i < 3; i++)
        for (int k = 0; k < 3; k++)
            C[i] += A[i][k] * B[k];
    Y.x = C[0];
    Y.y = C[1];
    Y.z = C[2];
    return Y;
}

void Point3 :: set(double x, double y, double z){
	this -> x = x;
	this -> y = y;
	this -> z = z;
}

double Point3 :: dot(Point3 X){
    double t = 0;
    t += (this -> x) * X.x;
    t += (this -> y) * X.y;
    t += (this -> z) * X.z;
    return t;
}

Point3 Point3 :: xet(Point3 X){
    Point3 Z;
    Z.x = (this -> y) * X.z - (this -> z) * X.y;
    Z.y = (this -> z) * X.x - (this -> x) * X.z;
    Z.z = (this -> x) * X.y - (this -> y) * X.x;
    return Z;
}

double Point3 :: dist(){
    double t = this -> dot(*this);
    return sqrt(t);
}

Point3 Point3 :: e(){
    Point3 Z = *this;
    double l = this -> dist();
    Z = Z * (1.0 / l);
    return Z;
}

Point3 Point3 :: neg(){
	Point3 Z = *this;
    Z.x = -Z.x;
    Z.y = -Z.y;
    Z.z = -Z.z;
}

double Point3 :: get_angle(Point3 X){
    double l = this -> dot(X);
    double cosa = l / (this -> dist()) / X.dist();
    return acos(cosa);
}

Point3 Point3 :: Rotate3(Point3 X, double selta){
    int A[3][3];
    Point3 Y;
    double x = X.x, y = X.y, z = X.z;
    double coss = cos(selta);
    double sins = sin(selta);
    A[0][0] = coss + x * x * (1 - coss);
    A[0][1] = x * y * (1 - coss) - z * sins;
    A[0][2] = x * z * (1 - coss) + y * sins;
    A[1][0] = y * x * (1 - coss) + z * sins;
    A[1][1] = coss + y * y * (1 - coss);
    A[1][2] = y * z * (1 - coss) - x * sins;
    A[2][0] = z * x * (1 - coss) + y * sins;
    A[2][1] = z * y * (1 - coss) + x * sins;
    A[2][2] = coss + z * z * (1 - coss);
    Y = A * X;
    return Y;
}

void Color :: align(){
    for (int i = 0; i < 4; i++){
        int x = a[i];
        a[i] = x;
    }
}

void Color :: set(double x, double y, double z, double w){
	this -> a[0] = x;
	this -> a[1] = y;
	this -> a[2] = z;
	this -> a[3] = w;
}

Color Color :: operator + (Color T){
    Color Z;
    for (int i = 0; i < 3; i++)
        Z.a[i] = this -> a[i] + T.a[i];
    Z.a[3] = 255;
    return Z;
}

Color Color :: operator * (double t){
    Color Z;
    for (int i = 0; i < 4; i++)
        Z.a[i] = this -> a[i] * t;
    return Z;
}

void Sphere :: set(double x, double y, double z, double r){
	(*this).center.set(x, y, z);
	this -> radius = r;
}

double Sphere :: cross_test(Line X){
	double t = (this -> center - X.source).xet(X.direct - X.source).dist();
    double l1 = (this -> center - X.source).dist();
    double d = t / l1;
    if (d >= radius) return inf;
    double A[3];
    double B[3];
    A[0] = X.direct.x;
    A[1] = X.direct.y;
    A[2] = X.direct.z;
    B[0] = X.source.x - center.x;
    B[1] = X.source.y - center.y;
    B[2] = X.source.z - center.z;
    double a = A[0] * A[0] + A[1] * A[1] + A[2] * A[2];
    double b = (A[0] * B[0] + A[1] * B[1] + A[2] * B[2]) * 2;
    double c = B[0] * B[0] + B[1] * B[1] + B[2] * B[2] - this -> radius * this -> radius;
    double x = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
    return x;
};

void Ball :: set_index(double reflectivity, double refractivity, double index){
	this -> reflectivity = reflectivity;
	this -> refractivity = refractivity;
	this -> index = index;
}

void Screen :: set(int width, int height, double z){
	this -> width = width;
	this -> height = height;
	this -> z = z;
    for (int i = 0; i <= width; i++)
        for (int j = 0; j <= height; j++)
            color[i][j].set(0, 0, 0, 0);
}
