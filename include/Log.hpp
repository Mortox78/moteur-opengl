#pragma once

#include <fstream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Model.hpp"
#include "Texture.hpp"
#include "Transform.hpp"

namespace Core
{
    namespace Debug
    {
        class Log
        {
            public:
                Log(){}
                ~Log(){}

                static bool is_file_opened(std::ifstream& file, const char* fileName);
                static bool check_is_window_created(GLFWwindow* window);
                static void display_model_data(Resources::Model& model);
                static void display_data_texture(Resources::Texture& texture);
                static void check_is_image_loaded(unsigned char* image, const char* fileName);
                static void check_shader_compil(unsigned int& shader);
                static void check_shader_program_compil(unsigned int& shaderProgram);
                static void display_transform_data(Physics::Transform& transform);
                static void init_glfw_failed();
                static void glad_load_gl_failed();
        };
    }
}