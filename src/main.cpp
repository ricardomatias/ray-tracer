#include <iostream>

#include "vec3.hpp"
#include "ray.hpp"

#define LOG(x) std::cout << (x) << std::endl

// `t*t*dot(B​ ,​ B​)​ + 2*t*dot(B​, A -​ ​C​) + dot(A​ - C, A​ - ​C​) - R*R = 0`
float hit_sphere(const vec3 &center, float radius, const ray &r) {
    vec3 oc = r.origin() - center;

    float a = dot(r.direction(), r.direction());
    float b = 2 * dot(r.direction(), oc);
    float c = dot(oc, oc) - radius * radius;

    float discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return -1;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}

vec3 color(const ray &r) {
    float t = hit_sphere(vec3(0.f, 0.f, -1.f), 0.5, r);

    if (t > 0.f) {
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0.f, 0.f, -1.f));

        return 0.5 * (N + 1.f);
    }

    vec3 unit_direction = unit_vector(r.direction());

    t = (1.0f + unit_direction.y()) * 0.5f;

    return (1.0f - t) * vec3(1.0f) + (t * vec3(0.5f, 0.7f, 1.0f));
}

int main(int argc, const char** argv) {
    int nx = 200;
    int ny = 100;

    std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0f, -1.0f, -1.0f);
    vec3 horizontal(4.0f, 0.0f, 0.0f);
    vec3 vertical(0.0f, 2.0f, 0.0f);
    vec3 origin(0.0f, 0.0f, 0.0f);

    for (int j = ny - 1; j >= 0; j--)
    {
        for (int i = 0; i < nx; i++)
        {
            float u = float(i) / nx;
            float v = float(j) / ny;

            vec3 target(u * horizontal.x(), v * vertical.y(), 0.f);
            
            ray r(origin, lower_left_corner + target);

            vec3 col = color(r);

            int ir = int(255.99f * col[0]);
            int ig = int(255.99f * col[1]);
            int ib = int(255.99f * col[2]);

            std::cout << ir << " " << ig  << " " << ib << "\n";
        }
    }
    
    return 0;
}
