#pragma once

#include "Graph.hpp"
#include "Light.hpp"
#include "Camera.hpp"

namespace Resources
{
    class Scene
    {
        public:
            Scene();
            ~Scene();

            std::vector<Core::DataStructure::Graph> graphs;
            LowRenderer::Light                      light;
            LowRenderer::Camera                     camera;

            void display();
    };
}