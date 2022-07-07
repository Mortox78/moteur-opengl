#pragma once

#include <iostream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SOIL.h>

namespace Resources
{
    class Texture
    {
        private:
            std::string name;
            bool loaded = false;
            GLuint texture = 0;
            int width;
            int height;


        public:
            Texture();
            Texture(const char* fileName);
            ~Texture();

            void load_texture(const char* fileName);
            void bind();

            std::string get_name();
            int         get_width();
            int         get_height();
            bool        is_loaded();
    };
}