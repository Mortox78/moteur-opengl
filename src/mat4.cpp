#include <iostream>
#include <assert.h>
#include <cmath>
#include "mat.h"
#include "mat4.h"
#include "vec3.h"
#include <vector>
#include <assert.h>

using namespace Core::Maths;

mat4::mat4()
{
    array.resize(16, 0.f);
    n = 4;
    m = 4;
}

mat4::~mat4()
{

}

mat4::mat4(const mat& mat)
{
    assert(mat.n == 4 && mat.m == 4);
    array.resize(16, 0.f);
    n = 4;
    m = 4;
    array = mat.array;
}

mat4 mat4::CreateScaleMatrix(const vec3& vec3)
{
    mat4 matScale;

    matScale.accessor(0, 0) = vec3.x;
    matScale.accessor(1, 1) = vec3.y;
    matScale.accessor(2, 2) = vec3.z;
    matScale.accessor(3, 3) = 1;

    return matScale;
}

mat4 mat4::CreateTranslationMatrix(const vec3& vec3)
{
    mat4 matTranslate = mat4::identity(4);

    matTranslate.accessor(0, 3) = vec3.x;
    matTranslate.accessor(1, 3) = vec3.y;
    matTranslate.accessor(2, 3) = vec3.z;

    return matTranslate;
}

mat4 mat4::CreateXRotationMatrix(const float& angleX)
{
    mat4 matRotateX = mat4::identity(4);

    matRotateX.accessor(1, 1) = cos(angleX);
    matRotateX.accessor(1, 2) = -sin(angleX);
    matRotateX.accessor(2, 1) = sin(angleX);
    matRotateX.accessor(2, 2) = cos(angleX);

    return matRotateX;
}

mat4 mat4::CreateYRotationMatrix(const float& rotAngleY)
{
    mat4 matRotateY = mat4::identity(4);

    matRotateY.accessor(0, 0) = cos(rotAngleY);
    matRotateY.accessor(0, 2) = sin(rotAngleY);
    matRotateY.accessor(2, 0) = -sin(rotAngleY);
    matRotateY.accessor(2, 2) = cos(rotAngleY);

    return matRotateY;
}

mat4 mat4::CreateZRotationMatrix(const float& angleZ)
{
    mat4 matRotateZ = mat4::identity(4);

    matRotateZ.accessor(0, 0) = cos(angleZ);
    matRotateZ.accessor(0, 1) = -sin(angleZ);
    matRotateZ.accessor(1, 0) = sin(angleZ);
    matRotateZ.accessor(1, 1) = cos(angleZ);

    return matRotateZ;
}

// vec3 contains the angles that we need in order to create the matrix rotation
mat4 mat4::CreateFixedAngleEulerRotationMatrix(const vec3& vec3)
{
    mat matRotX = CreateXRotationMatrix(vec3.x * M_PI / 180);
    mat matRotY = CreateYRotationMatrix(vec3.y * M_PI / 180);
    mat matRotZ = CreateZRotationMatrix(vec3.z * M_PI / 180);

    return matRotY * matRotX * matRotZ;
}

mat4 mat4::CreateTRSMatrix(const vec3& scale, const vec3& rotation, const vec3& translation)
{
    mat4 matT = CreateTranslationMatrix(translation);
    mat4 matR = CreateFixedAngleEulerRotationMatrix(rotation);
    mat4 matS = CreateScaleMatrix(scale);

    mat4 matRS = matR * matS;

    return matT * matRS;
}


mat4 operator*(const mat4& mat1, float factor)
{
    assert(factor != 0 && mat1.n == 4 && mat1.m == 4);
    mat4 newMatrix;

    for (int i = 0; i < newMatrix.n * newMatrix.m; ++i)
    {
        newMatrix.array[i] = mat1.array[i] * factor;
    }
    
    return newMatrix;
}


vec4 operator*(mat4& mat1, const vec4& vecToMultiply)
{
    mat4 vec4casted;
    vec4casted.accessor(0, 0) = vecToMultiply.x;
    vec4casted.accessor(1, 0) = vecToMultiply.y;
    vec4casted.accessor(2, 0) = vecToMultiply.z;
    vec4casted.accessor(3, 0) = vecToMultiply.w;

    mat4 result = mat1 * vec4casted;

    return vec4(result.accessor(0, 0), result.accessor(1, 0), result.accessor(2, 0), result.accessor(3, 0));
}