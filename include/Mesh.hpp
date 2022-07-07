#pragma once

#include "Model.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Mesh.hpp"
#include "Light.hpp"
#include "vec3.h"

namespace LowRenderer
{
    class Mesh
    {
        public:
            Mesh();
            Mesh(const char* objFileName, const char* texFileName);
            ~Mesh();

            Resources::Model        model;
            Resources::Shader       shader;
            Resources::Texture      texture;
            Physics::Transform      transform;
            GLuint VBO, VAO;

            void load_buffers();
            void update(Camera& camera); // only update the mesh
            void draw(Camera& camera); // only draw the current mesh

            void update(Camera& camera, Core::Maths::mat4& parentMatTRS, LowRenderer::Light& light); // update mesh with parentMatTRS
            void draw(Camera& camera, Core::Maths::mat4& parentMatTRS, LowRenderer::Light& light); // draw the mesh with a parentMatTRS
    };
}