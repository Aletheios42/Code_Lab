#include "sphere.h"

bool hit_sphere(t_vec3 center, double radius, t_ray r) {
    t_vec3 oc = vec3_sum(center, r.origin);
    double a = vec3_dot(r.dir, r.dir);
    double b = -2.0 * vec3_dot(r.dir, oc);
    double c = vec3_dot(oc, oc) - radius*radius;
    double discriminant = b*b - 4*a*c;
    return (discriminant >= 0);
}
