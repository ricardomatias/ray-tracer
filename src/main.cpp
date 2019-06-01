#include <iostream>
#include <fstream>
#include <float.h>

#include "sphere.hpp"
#include "hitablelist.hpp"

#define LOG(x) std::cout << (x) << std::endl

vec3 color(const ray &r, hitable *world)
{
    hit_record rec;

    if (world->hit(r, 0.0, FLT_MAX, rec))
    {
        return 0.5f * vec3(rec.normal.x() + 1.0f, rec.normal.y() + 1.0f, rec.normal.z() + 1.0f);
    }
    else
    {
        vec3 unit_direction = unit_vector(r.direction());

        float t = 0.5f * (unit_direction.y() + 1.0f);

        return (1.0f - t) * vec3(1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
    }
}

int main(int argc, const char **argv)
{
    int nx = 200;
    int ny = 100;

    std::ofstream outfile;
    outfile.open("image.ppm");

    outfile << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f, 0.0f, 0.0f);

    hitable *list[2];

    list[0] = new sphere(vec3(0.f, 0.f, -1.f), 0.5f);
    list[1] = new sphere(vec3(0.f, -100.5f, -1.f), 100.f);

    hitable *world = new hitable_list(list, 2);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / nx;
            float v = float(j) / ny;

            ray r(origin, lower_left_corner + u * horizontal + v * vertical);

            vec3 p = r.point_at_parameter(1.f);
            vec3 col = color(r, world);

            int ir = int(255.99f * col[0]);
            int ig = int(255.99f * col[1]);
            int ib = int(255.99f * col[2]);

            outfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    outfile.close();

    return 0;
}
