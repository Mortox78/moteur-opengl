#pragma once

#include "Scene.hpp"
#include "ResourcesManager.hpp"
#include "Camera.hpp"
#include "Graph.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#define SCREEN_WIDTH  1024.f
#define SCREEN_HEIGHT 768.f

class Engine
{
    private:
        float deltaTime;
            float           oldTimeSinceStart  = 0;
            float           time               = 0;
            unsigned int    nbFrames              = 0;
        bool                running            = true;

        float rotAngleY = 0;

        void                init_glfw();
        GLFWwindow*         init_glfw_and_create_window();
        void                update_delta_time();
        void                update_input();

    public:
        Engine();
        ~Engine();

        GLFWwindow*                     window;
        Resources::Scene                scene;
        Resources::ResourcesManager     resourcesManager;


        void update();
        bool is_running();

};