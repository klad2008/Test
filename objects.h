#pragma once

#include <cstdio>
#include <cmath>

class Point3{
	public:
	double x, y, z;
	void set(double, double, double);
	Point3 e();
	Point3 neg();
	double dist();
    double dot(Point3);
	Point3 xet(Point3);
	double get_angle(Point3);
	Point3 Rotate3(Point3, double);
    Point3 operator + (Point3 T);
    Point3 operator - (Point3 T);
    Point3 operator * (double t);
	Point3(){}
	Point3(double x, double y, double z){
		this -> x = x;
		this -> y = y;
		this -> z = z;
	}
};

class Color{
	public:
	double a[4];
    void align();
	void set(double , double , double , double );
    Color operator + (Color T);
    Color operator * (double t);
};

class Line{
	public:
	Point3 source, direct;
};

class Sphere{
	public:
	Point3 center;
	double radius;
	void set(double , double , double , double );
	double cross_test(Line );
};

class Ball{
	public:
	Sphere sphere;
	double reflectivity, refractivity, index;
	void set_index(double , double , double );
};

class Source{
	public:
	Sphere sphere;
	Color color;
};

class Screen{
	public:
	int width, height;
	double z;
    Color color[2000][2000];
	void set(int width, int height, double z);
};

class Ray{
	public:
	Line line;
	Color color;
};

