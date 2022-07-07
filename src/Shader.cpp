#include "Shader.hpp"

#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>

#include "Log.hpp"

using namespace Resources;

Shader::Shader()
{
    shaderProgram = load_shader();
}

Shader::~Shader()
{

}

unsigned int Shader::load_shader()
{
    vertexShader   = load_vertex_shader();
    fragmentShader = load_fragment_shader();
    // SHADER PROGRAM
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // CHECK IF COMPIL WORKED WITH SHADER PROGRAM
    Core::Debug::Log::check_shader_program_compil(shaderProgram);

    return shaderProgram;
}


unsigned int Shader::load_vertex_shader()
{
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 texCoord;\n"
        "layout (location = 2) in vec3 normal;\n"
        "out vec3 Normal;\n"
        "out vec2 TexCoord;\n"
        "out vec3 FragPos;\n"
        "uniform mat4 camera;\n"
        "uniform mat4 projection;\n"
        "uniform mat4 transform;\n"
        "void main()\n"
        "{\n"
        "   FragPos     = vec3(transform * vec4(aPos.x, aPos.y, aPos.z, 1.0));\n"
        "   Normal      = mat3(transpose(inverse(transform))) * normal;\n"
        "   TexCoord    = texCoord;\n"
        "   gl_Position = projection * (camera * vec4(FragPos, 1.0));\n"
        "}\0";

    // VERTEX SHADER
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check if compilation worked
    Core::Debug::Log::check_shader_compil(vertexShader);

    return vertexShader;
}


unsigned int Shader::load_fragment_shader()
{
    const char* fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 TexCoord;\n"
    "in vec3 Normal;\n"
    "in vec3 FragPos;\n"
    "uniform sampler2D ourTexture1;\n"
    "uniform vec3 lightPos;\n"
    "uniform vec3 viewPos;\n"
    "uniform vec3 lightColor;\n"
    "void main()\n"
    "{\n"
        // ambient
        "float ambientStrenght = 0.3;\n"
        "vec3 ambient = ambientStrenght * lightColor;\n"
        
        // diffuse
        "vec3 norm = normalize(Normal);\n"
        "vec3 lightDir = normalize(lightPos - FragPos);\n"
        "float diff = max(dot(norm, lightDir), 0.0);\n"
        "vec3 diffuse = diff * lightColor;\n"

        // specular
        "float specularStrenght = 0.5;\n"
        "vec3 viewDir = normalize(viewPos - FragPos);\n"
        "vec3 reflectDir = reflect(lightDir * -1, norm);\n"
        "float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);\n"
        "vec3 specular = specularStrenght * spec * lightColor;\n"

        "vec3 result = (ambient + diffuse + specular);\n"

         "FragColor = texture(ourTexture1, TexCoord) * vec4(result, 1.0);\n"
    "}\n"; 

    // FRAGMENT SHADER
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check if compilation worked
    Core::Debug::Log::check_shader_compil(fragmentShader);

    return fragmentShader;
}

void Shader::use_program()
{
    glUseProgram(shaderProgram);
}