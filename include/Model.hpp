#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include "vec2.hpp"
#include "vec3.h"

namespace Resources
{
    class Model
    {
        private:
            void clear_model_data();
            void create_convertedVertices();
            void extract_obj_vertex(std::ifstream& file, std::vector<Core::Maths::vec3>& temp_vertices);
            void extract_obj_uv(std::ifstream& file, std::vector<Core::Maths::vec2>& temp_uvs);
            void extract_obj_normal(std::ifstream& file, std::vector<Core::Maths::vec3>& temp_normals);
            void extract_obj_face(std::ifstream& file, std::vector<unsigned int>& vertexIndices, std::vector<unsigned int>& uvIndices, std::vector<unsigned int>& normalIndices);


            std::string name;
            bool loaded = false;

            std::vector<Core::Maths::vec3>    vertices;
            std::vector<Core::Maths::vec2>    uvs;
            std::vector<Core::Maths::vec3>    normals;
            std::vector<float>                convertedVertices;

        public:
            Model();
            Model(const char* fileName);
            ~Model();
            
            void load_obj(const char* fileName);

            std::string                       get_name();
            std::vector<Core::Maths::vec3>    get_vertices();
            std::vector<Core::Maths::vec2>    get_uvs();
            std::vector<Core::Maths::vec3>    get_normals();
            std::vector<float>                get_converted_vertices();
            bool                              is_loaded();
    };
}

