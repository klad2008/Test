#include <cstdio>
#include <cmath>
#include <vector>

#include "const_data.h"
#include "objects.h"
#include "opengl_test.h"

Point3 camera;
Screen screen;
Ball ball_1;
Source source_1;
OpenGL_Test pencil;

std::vector <Ball *> obstacle;
std::vector <Source *> light_source;

void Init(){
    source_1.sphere.set(50, 0, -200, 100);
    source_1.color.set(1, 1, 1, 1);
    ball_1.sphere.set(50, 0, -50, 25);
    ball_1.set_index(0.9, 0, 1);
    camera.set(0, 0, 400);
    screen.set(200, 100, 0);
}

void Diego(Ray &ray, double alpha, const int step){
    double t;
    double Angle_Incident, Angle_Incident_sin;
    double Angle_Refraction, Angle_Refraction_sin;
    Ray ray_reflectivity, ray_refractivity, ray_normal;
    Point3 Intersection;
    Ball *p_b = NULL;
    Source *p_s = NULL;
    int status = 0;
    ray.color.set(0, 0, 0, 0);
    if (alpha < alpha_eps_limit){
        return;
    }

    t = inf;
    for (auto ball : obstacle){
        double tt = (*ball).sphere.cross_test(ray.line);
        if (tt < t){
            t = tt;
            p_b = ball;
            status = 1;
        }
    }
    for (auto source: light_source){
        double tt = (*source).sphere.cross_test(ray.line);
        if (tt < t){
            t = tt;
            p_s = source;
            status = 2;
        }
    }
    if (status == 0){
        ray.color.set(0, 0, 0, 0);
        return;
    }

    if (status == 1){
        Intersection = ray.line.source + ray.line.direct * t;
        ray_normal.line.direct = (Intersection - (*p_b).sphere.center).e();
        Angle_Incident = ray.line.direct.neg().get_angle(ray_normal.line.direct);
        Angle_Incident_sin = sin(Angle_Incident);
        Angle_Refraction_sin = Angle_Incident / (p_b -> index);
        Angle_Refraction = asin(Angle_Refraction_sin);

        ray_reflectivity.line.source = Intersection;
        ray_reflectivity.line.direct = ray.line.direct.neg().Rotate3(ray_normal.line.direct, pi);
        Diego(ray_reflectivity, alpha * (*p_b).reflectivity, step + 1);

        ray_refractivity.line.source = Intersection;
        if ((ray.line.direct.xet(ray_normal.line.direct)).dist() < eps){
            ray_refractivity.line.direct = ray.line.direct;
        }
        else{
            Point3 normal2 = ray.line.direct.xet(ray_normal.line.direct);
            ray_refractivity.line.
                    direct = ray.line.direct.Rotate3(normal2, Angle_Incident - Angle_Refraction);
        }
        Diego(ray_refractivity, alpha * (*p_b).refractivity, step + 1);

        ray.color = ray_reflectivity.color * (*p_b).reflectivity + ray_refractivity.color * (*p_b).refractivity;
    }

    if (status == 2){
        ray.color = (*p_s).color;
    }
}


Color calc(Point3 Light_Point){
    Ray ray;
    ray.line.source = camera;
    ray.line.direct = (Light_Point - camera).e();
    ray.color.set(0, 0, 0, 0);
    obstacle.clear();
    light_source.clear();
    obstacle.push_back(&ball_1);
    light_source.push_back(&source_1);
    Diego(ray, 1, 0);
//    ray.color.align();
    return ray.color;
}

void Work(){
    for (int i = 0; i <= screen.width; i++)
        for (int j = 0; j <= screen.height; j++)
            screen.color[i][j] = calc(Point3(i, j, screen.z));
}

void Test(){
    Init();
    Work();
    pencil.Draw(screen);
}

int main(){
    Test();
}
