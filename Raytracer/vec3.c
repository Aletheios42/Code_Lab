#include <math.h>

typedef struct s_vec3 {
    double coor[3];
} t_vec3;

t_vec3 vec3_init(double x, double y, double z) {
    t_vec3 v;

    v.coor[0] = x;
    v.coor[1] = y;
    v.coor[2] = z;
    return v;
}

double vec3_get(t_vec3 *v, int index) {
    if (index < 0 || index > 2)
        return 0.0;
    return v->coor[index];
} 

t_vec3 vec3_sum(t_vec3 v1, t_vec3 v2) {
    t_vec3 result;

    result.coor[0] = v1.coor[0] + v2.coor[0];
    result.coor[1] = v1.coor[1] + v2.coor[1];
    result.coor[2] = v1.coor[2] + v2.coor[2];
    return result;
}

t_vec3 vec3_subtract(t_vec3 v1, t_vec3 v2) {
    t_vec3 result;

    result.coor[0] = v1.coor[0] - v2.coor[0];
    result.coor[1] = v1.coor[1] - v2.coor[1];
    result.coor[2] = v1.coor[2] - v2.coor[2];
    return result;
}

t_vec3 vec3_multuply(t_vec3 v1, t_vec3 v2) {
    t_vec3 result;

    result.coor[0] = v1.coor[0] * v2.coor[0];
    result.coor[1] = v1.coor[1] * v2.coor[1];
    result.coor[2] = v1.coor[2] * v2.coor[2];
    return result;
}

t_vec3 vec3_divide(t_vec3 v1, t_vec3 v2) {
    t_vec3 result;

    result.coor[0] = (v2.coor[0] != 0) ? v1.coor[0] / v2.coor[0] : 0;
    result.coor[1] = (v2.coor[1] != 0) ? v1.coor[1] / v2.coor[1] : 0;
    result.coor[2] = (v2.coor[2] != 0) ? v1.coor[2] / v2.coor[2] : 0;
    return result;
}

t_vec3 vec3_divide_scalar(t_vec3 v1, double scalar) {
    t_vec3 result;

    if (scalar > 0) {
        result.coor[0] =  v1.coor[0] / scalar;
        result.coor[1] =  v1.coor[1] / scalar;
        result.coor[2] =  v1.coor[2] / scalar;
    }
    else
        result = vec3_init(0,0,0);
    return result;
}

double vec3_lenght(t_vec3 v) {
    double result;

    result = v.coor[0] * v.coor[0] + v.coor[1] * v.coor[1] + v.coor[2] * v.coor[2];
    return sqrt(result);
}

double vec3_lenght_squared(t_vec3 v) {

    double result;

    result = v.coor[0] * v.coor[0] + v.coor[1] * v.coor[1] + v.coor[2] * v.coor[2];
    return result;
}

t_vec3 vec3_normalize(t_vec3 v) {
    t_vec3 result;
    double length;

    length = vec3_lenght(v);
    if (length > 0)
        result = vec3_divide_scalar(v, length);
    else
        result = vec3_init(0,0,0);
    return result;
}
