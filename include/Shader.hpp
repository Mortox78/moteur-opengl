#pragma once

namespace Resources
{
    class Shader
    {
        private:
            unsigned int load_shader();
            unsigned int load_vertex_shader();
            unsigned int load_fragment_shader();

        public:
            Shader();
            ~Shader();

            unsigned int vertexShader;
            unsigned int fragmentShader;
            unsigned int shaderProgram;

            void use_program();
    };
}