#include <iostream>
#include <math.h>
#include "vec3.h"
#include "vec4.h"

using namespace Core::Maths;

vec3::vec3()
{

}

vec3::vec3(const float& x, const float& y, const float& z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

vec3::vec3(const vec4& copyVec)
{
    this->x = copyVec.x;
    this->y = copyVec.y;
    this->z = copyVec.z;
}

vec3::~vec3()
{

}

float vec3::GetMagnitude() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

void vec3::Normalize()
{
    float magnitude = GetMagnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}

vec3 operator+(vec3 v1, vec3 v2)
{
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

vec3 operator*(vec3 vec, float factor)
{
    return {vec.x * factor, vec.y * factor, vec.z * factor};
}

vec3 operator-(vec3 v1, vec3 v2)
{
    return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}
