#include <iostream>

#include "Scene.hpp"
#include "Graph.hpp"
#include "Camera.hpp"

using namespace Resources;

Scene::Scene()
{

}

Scene::~Scene()
{

}


void Scene::display()
{
    for (std::vector<Core::DataStructure::Graph>::iterator it = graphs.begin(); it != graphs.end(); ++it)
    {
        it->display(camera, light);
    }
}