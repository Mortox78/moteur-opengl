#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Light.hpp"
#include "vec3.h"

using namespace LowRenderer;

Light::Light()
{
    this->ambientComponent  = 0;
    this->diffuseComponent  = 0;
    this->specularComponent = 0;
    this->position          = {0, 1, 0};
    this->color             = {1, 1, 1};
}

Light::Light(const Core::Maths::vec3& position, const Core::Maths::vec3& components)
{
    this->position          = position;
    this->ambientComponent  = components.x;
    this->diffuseComponent  = components.y;
    this->specularComponent = components.z;
    this->color             = {1, 0, 0};
}

Light::~Light()
{

}

void Light::apply(Resources::Shader& shader)
{
    unsigned int lightPosLoc = glGetUniformLocation(shader.shaderProgram, "lightPos");
    glUniform3f(lightPosLoc, position.x, position.y, position.z);

    unsigned int lightColorLoc = glGetUniformLocation(shader.shaderProgram, "lightColor");
    glUniform3f(lightColorLoc, color.x, color.y, color.z);
}