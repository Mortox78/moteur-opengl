#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "mat.h"
#include "vec3.h"
#include "vec4.h"

namespace Core
{
    namespace Maths
    {
        class mat4 : public mat
        {
            public:

            mat4();
            mat4(const mat& mat);
            ~mat4();

            static mat4 CreateScaleMatrix(const vec3& vec3);
            static mat4 CreateTranslationMatrix(const vec3& vec3);
            static mat4 CreateXRotationMatrix(const float& angleX);
            static mat4 CreateYRotationMatrix(const float& rotAngleY);
            static mat4 CreateZRotationMatrix(const float& angleZ);
            static mat4 CreateFixedAngleEulerRotationMatrix(const vec3& vec3);
            static mat4 CreateTRSMatrix(const vec3& scale, const vec3& rotation, const vec3& translation);
        };

        mat4 operator*(const mat4& mat1, float factor);

        vec4 operator* (mat4& mat1, const vec4& vecToMultiply);
    }
}
#endif