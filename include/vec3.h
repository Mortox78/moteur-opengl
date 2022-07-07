#ifndef _vec3_H_
#define _vec3_H_

#include "vec4.h"

namespace Core
{
    namespace Maths
    {
        class vec3
        {
            public:
                vec3();
                vec3(const float& x, const float& y, const float& z);
                vec3(const vec4& copyVec);
                ~vec3();

                float x;
                float y;
                float z;

                float GetMagnitude() const;
                void Normalize();

        };

        vec3 operator+(vec3 v1, vec3 v2);

        vec3 operator-(vec3 v1, vec3 v2);

        vec3 operator*(vec3 vec, float factor);
    }
}

#endif