#include <iostream>
#include <fstream>

#include "Log.hpp"
#include "Model.hpp"


using namespace Core::Debug;

bool Log::is_file_opened(std::ifstream& file, const char* fileName)
{
    if (file.fail())
    {
        std::cout << "Error while opening file \"" << fileName <<  "\"" << std::endl;
        return false;
    }
    else
    {
        std::cout << "File \"" << fileName << "\" opened" << std::endl;
        return true;
    }
}


void Log::display_model_data(Resources::Model& model)
{
    std::cout << "===================================" << std::endl;
    std::cout << "Model's name : "                     << model.get_name() << std::endl;
    std::cout << "vertices.size()           : "        << model.get_vertices().size() << std::endl;
    std::cout << "uvs.size()                : "        << model.get_uvs().size() << std::endl;
    std::cout << "normals.size()            : "        << model.get_normals().size() << std::endl;
    std::cout << "converted_vertices.size() : "        << model.get_converted_vertices().size() << std::endl;
}


void Log::check_is_image_loaded(unsigned char* image, const char* fileName)
{
    if (!image)
    {
        std::cout << "Error while opening image \"" << fileName << "\"" << std::endl;
    }
    else
    {
        std::cout << "Image \"" << fileName << "\" loaded" << std::endl;
    }
    
}


void Log::display_data_texture(Resources::Texture& texture)
{
    std::cout << "===================================" << std::endl;
    std::cout << "Texture's name : " << texture.get_name()   << std::endl;
    std::cout << "width          : " << texture.get_width()  << std::endl;
    std::cout << "height         : " << texture.get_height() << std::endl;

}

void Log::check_shader_compil(unsigned int& shader)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void Log::check_shader_program_compil(unsigned int& shaderProgram)
{
    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}


void Log::display_transform_data(Physics::Transform& transform)
{
    std::cout << "=====================================" << std::endl;
    std::cout << "transform.translate : x = " << transform.translate.x << " y = " << transform.translate.y << " z = " << transform.translate.z << std::endl;
    std::cout << "transform.rotate :    x = " << transform.rotate.x    << " y = " << transform.rotate.y    << " z = " << transform.rotate.z << std::endl;
    std::cout << "transform.scale :     x = " << transform.scale.x     << " y = " << transform.scale.y     << " z = " << transform.scale.z << std::endl;
    std::cout << "=====================================" << std::endl;
}

void Log::init_glfw_failed()
{
    std::cout << "glfwInit Failed." << std::endl;
}


bool Log::check_is_window_created(GLFWwindow* window)
{
    if (!window)
    {
        std::cout << stderr << " glfwCreateWindow failed." << std::endl;
        glfwTerminate();
        return false;
    }
    return true;
}

void Log::glad_load_gl_failed()
{
    std::cout << stderr << " gladLoadGL failed" << std::endl;
    glfwTerminate();
}