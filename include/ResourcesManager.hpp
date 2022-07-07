#pragma once

#include "Mesh.hpp"
#include "Model.hpp"
#include "Texture.hpp"

namespace Resources
{
    class ResourcesManager
    {
        public:
            ResourcesManager();
            ~ResourcesManager();

            std::vector<Model>      models;
            std::vector<Texture>    textures;

            LowRenderer::Mesh load_mesh(const char* objFileName, const char* texFileName);

    };
}