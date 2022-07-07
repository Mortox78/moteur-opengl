#include <iostream>

#include <SDL2/SDL.h>

#include "Engine.hpp"
#include "Log.hpp"



Engine::Engine()
{
    window = init_glfw_and_create_window();
    glEnable(GL_DEPTH_TEST);

    // Camera
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Engine::~Engine()
{

}

void Engine::init_glfw()
{
    if (!glfwInit())
    {
        Core::Debug::Log::init_glfw_failed();
        running = false;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    glfwSwapInterval(1);
}

GLFWwindow* Engine::init_glfw_and_create_window()
{
    init_glfw();

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL 3.3", NULL, NULL);

    if (!Core::Debug::Log::check_is_window_created(window))
        return nullptr;

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
        Core::Debug::Log::glad_load_gl_failed();
        return nullptr;
    }

    return window;
}

void Engine::update_delta_time()
{
	//we look for the time of execution since we initialized SDL
    float current_time 		= SDL_GetTicks();
	//and here we calculate the time of execution of the loop
    deltaTime			    = (time > 0) ? ((current_time - time) / 1000.f) : 1.0f / 60.0f;
    time 					= current_time;

	oldTimeSinceStart += deltaTime;
	nbFrames++;

	if (oldTimeSinceStart > 1)
	{
		std::cout << "FPS : " << ((float)nbFrames/oldTimeSinceStart) << std::endl;
		oldTimeSinceStart = 0;
		nbFrames = 0;
	}
}

void Engine::update()
{
    update_delta_time();
    // input
    update_input();
    scene.camera.manage_cam(window, deltaTime);

    // update matTransform and draw
    scene.display();
    // swap buffers and clear
    glfwSwapBuffers(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.62f, 0.62f, 0.62f, 1.f);
}

bool Engine::is_running()
{
    return running;
}

void Engine::update_input()
{
    // input
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_Y))
        scene.graphs[0].mesh.transform.rotate.y += 2;
    if (glfwGetKey(window, GLFW_KEY_X))
        scene.graphs[0].mesh.transform.rotate.x += 2;
    if (glfwGetKey(window, GLFW_KEY_Z))
        scene.graphs[0].mesh.transform.rotate.z += 2;
    if (glfwGetKey(window, GLFW_KEY_KP_ADD))
    {
        scene.graphs[0].mesh.transform.scale.x += 0.01;
        scene.graphs[0].mesh.transform.scale.y += 0.01;
        scene.graphs[0].mesh.transform.scale.z += 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT))
    {
        scene.graphs[0].mesh.transform.scale.x -= 0.01;
        scene.graphs[0].mesh.transform.scale.y -= 0.01;
        scene.graphs[0].mesh.transform.scale.z -= 0.01;
    }
    if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        running = false;
}