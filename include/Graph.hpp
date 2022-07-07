#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "Mesh.hpp"
#include "Camera.hpp"
#include "mat4.h"
#include "Light.hpp"


namespace Core
{
    namespace DataStructure
    {
        class Graph
        {
            public:
                Graph();
                Graph(LowRenderer::Mesh copyMesh);
                Graph(const char* objFileName, const char* texFileName);
                ~Graph();

                LowRenderer::Mesh  mesh;
                std::vector<Graph> childrens;

                void draw_all(LowRenderer::Camera& camera, Core::Maths::mat4& parentMatTRS, LowRenderer::Light& light);
                void display(LowRenderer::Camera& camera, LowRenderer::Light& light);
        };
    }
}