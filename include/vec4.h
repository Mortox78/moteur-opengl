#ifndef _vec4_H_
#define _vec4_H_

namespace Core
{
    namespace Maths
    {
        class vec3;

        class vec4
        {
            public:
            vec4();
            vec4(const vec3& vec3);
            ~vec4();
            vec4(float x, float y, float z, float w);


            float x;
            float y;
            float z;
            float w;

            void Homogenize();
            float GetMagnitude() const;
            void Normalize();
        };

        vec4 operator+(vec4 v1, vec4 v2);
    }
}
#endif