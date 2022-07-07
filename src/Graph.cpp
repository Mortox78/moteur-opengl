#include <iostream>

#include "Graph.hpp"
#include "Mesh.hpp"
#include "mat4.h"
#include "Light.hpp"

using namespace Core::DataStructure;

Graph::Graph()
{

}

Graph::Graph(LowRenderer::Mesh copyMesh)
{
    this->mesh = copyMesh;
}

Graph::Graph(const char* objFileName, const char* texFileName)
{
    mesh = LowRenderer::Mesh(objFileName, texFileName);
}

Graph::~Graph()
{

}

void Graph::draw_all(LowRenderer::Camera& camera, Core::Maths::mat4& parentMatTRS, LowRenderer::Light& light)
{
    this->mesh.update(camera, parentMatTRS, light);
    this->mesh.draw(camera, parentMatTRS, light);
    Core::Maths::mat4 thisMeshMatTRS = this->mesh.transform.create_transform_matrix();
    // display our object's childrens
    for (std::vector<Graph>::iterator it = childrens.begin() ; it != childrens.end(); ++it)
    {
        it->draw_all(camera, thisMeshMatTRS, light);
    }
}

void Graph::display(LowRenderer::Camera& camera, LowRenderer::Light& light)
{
    Core::Maths::mat4 matWorld = Core::Maths::mat4::identity(4);

    // display our object's childrens
    this->draw_all(camera, matWorld, light);
}