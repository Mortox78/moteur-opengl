#include <iostream>
#include <math.h>
#include "vec4.h"
#include "vec3.h"

using namespace Core::Maths;

vec4::vec4()
{

}

vec4::~vec4()
{

}

vec4::vec4(const vec3& vec3)
{
    x = vec3.x;
    y = vec3.y;
    z = vec3.z;
    w = 1.f;
}


vec4::vec4(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

void vec4::Homogenize()
{
    if (w != 0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
}

float vec4::GetMagnitude() const
{
    return sqrt((x * x) + (y * y) + (z * z));
}

void vec4::Normalize()
{
    float magnitude = GetMagnitude();
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
}


vec4 operator+(vec4 v1, vec4 v2)
{
    return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w};
}


vec4 operator*(vec4 v1, vec4 v2)
{
    return {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w};
}