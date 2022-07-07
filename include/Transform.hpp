#pragma once

#include "vec3.h"
#include "mat4.h"

namespace Physics
{
    class Transform
    {
        public:
            Transform();
            ~Transform();

            Core::Maths::vec3 translate;
            Core::Maths::vec3 rotate;
            Core::Maths::vec3 scale;

            Core::Maths::mat4 create_transform_matrix();
    };
}