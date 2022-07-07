#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SOIL.h>

#include "Texture.hpp"
#include "Log.hpp"

using namespace Resources;

Texture::Texture()
{

}

Texture::Texture(const char* fileName)
{
    load_texture(fileName);
}


Texture::~Texture()
{

}


void Texture::load_texture(const char* fileName)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // generate texture
    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);

    // Set our texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Set texture filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* image = SOIL_load_image(fileName, &this->width, &this->height, 0, SOIL_LOAD_RGBA);
    Core::Debug::Log::check_is_image_loaded(image, fileName);

    // Load, create texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    SOIL_free_image_data(image);

    this->name = fileName;
    glBindTexture(GL_TEXTURE_2D, 0);
    loaded = true;
}

std::string Texture::get_name()
{
    return name;
}

int Texture::get_width()
{
    return width;
}

int Texture::get_height()
{
    return height;
}

void Texture::bind()
{
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

bool Texture::is_loaded()
{
    return loaded;
}