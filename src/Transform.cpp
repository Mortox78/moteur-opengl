#include <iostream>
#include <cmath>

#include "Transform.hpp"
#include "mat.h"
#include "mat4.h"

using namespace Physics;

Transform::Transform()
{
    translate = {0, 0, 0};
    rotate    = {0, 0, 0};
    scale     = {1, 1, 1};
}

Transform::~Transform()
{

}

Core::Maths::mat4 Transform::create_transform_matrix()
{
    return Core::Maths::mat4::CreateTRSMatrix(this->scale, this->rotate, this->translate);
}