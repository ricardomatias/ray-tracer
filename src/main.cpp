#include <iostream>
#include <fstream>
#include <random>

#include "float.h"

#include "Sphere.hpp"
#include "HitableList.hpp"
#include "Camera.hpp"

using namespace std;

Vec3 RandomInUnitSphere()
{
    Vec3 p;

    do {
        p = 2.0f * Vec3((rand() % 100 / float(100)), (rand() % 100 / float(100)), (rand() % 100 / float(100))) - Vec3(1.0f, 1.0f, 1.0f);
    } while (p.squared_length() >= 1.0);

    return p;
}

Vec3 color(const Ray &r, Hitable *world)
{
    hit_record rec;
    if (world->hit(r, 0.001f, MAXFLOAT, rec))
    {
        Vec3 target = rec.p + rec.normal + RandomInUnitSphere();
        return 0.5f * color(Ray(rec.p, target - rec.p), world);
    }
    else
    {
        Vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5f * (unit_direction.y() + 1.0f);

        return (1.0f - t) * Vec3(1.0f, 1.0f, 1.0f) + t * Vec3(0.5f, 0.7f, 1.0f);
    }
}

int main()
{

    ofstream outfile;
    outfile.open("image.ppm");

    int nx = 400;
    int ny = 200;

    int ns = 100;
    outfile << "P3\n"
            << nx << " " << ny << "\n255\n";

    Hitable *list[2];
    list[0] = new Sphere(Vec3(0.0f, 0.0f, -1.0f), 0.5f);
    list[1] = new Sphere(Vec3(0.0f, -100.5f, -1.0f), 100.0f);
    Hitable *world = new HitableList(list, 2);

    Camera cam;

    default_random_engine reng;
    uniform_real_distribution<float> uni_dist(0.0f, 1.0f);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            Vec3 col(0.0f, 0.0f, 0.0f);

            for (int s = 0; s < ns; s++)
            {
                float u = float(i + uni_dist(reng)) / float(nx);
                float v = float(j + uni_dist(reng)) / float(ny);
                
                Ray r = cam.getRay(u, v);

                col += color(r, world);
            }

            col /= float(ns);

            col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            outfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    outfile.close();
    return 0;
}
