#pragma once

#include "vec3.h"
#include "Shader.hpp"

namespace LowRenderer
{
    class Light
    {
        private:
            float ambientComponent;
            float diffuseComponent;
            float specularComponent;

        public:
            Core::Maths::vec3 position;
            Core::Maths::vec3 color;

            Light();
            Light(const Core::Maths::vec3& position, const Core::Maths::vec3& components);
            ~Light();

            void apply(Resources::Shader& shader);
    };
}