#include <cstdio>
#include <iostream>
#include <memory>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>
#include <SDL2/SDL.h>

#include "Shader.hpp"
#include "Model.hpp"
#include "Texture.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "ResourcesManager.hpp"
#include "Graph.hpp"
#include "Log.hpp"
#include "Scene.hpp"
#include "Light.hpp"
#include "Engine.hpp"

int main()
{
    Engine engine;
    if (!engine.is_running())
        return 0;

    Core::DataStructure::Graph graph(engine.resourcesManager.load_mesh("resources/Sword.obj" , "resources/Sword.png"));
    graph.childrens.push_back(engine.resourcesManager.load_mesh("resources/Cube.obj" , "resources/wall.jpg"));
    graph.childrens.push_back(engine.resourcesManager.load_mesh("resources/watch_tower.obj" , "resources/watch_tower.jpg"));
    graph.childrens.push_back(engine.resourcesManager.load_mesh("resources/Plante.obj" , "resources/wall.jpg"));
    graph.childrens[2].mesh.transform.scale       = {0.01, 0.01, 0.01};
    graph.childrens[2].mesh.transform.translate.z = -15;
    graph.childrens[0].mesh.transform.translate.y = 10;

    Resources::Scene scene;
    scene.graphs.push_back(graph);
    scene.light.position = {4, 0, 0};
    scene.graphs[0].mesh.shader.use_program();

    engine.scene = scene;

    while (engine.is_running())
    {
        engine.update();
    }

    glfwTerminate();
    return 0;
}