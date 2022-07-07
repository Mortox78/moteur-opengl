#include <cstdio>
#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <algorithm>
#include <assert.h>

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <GL/gl.h>

#include "Model.hpp"
#include "vec2.hpp"
#include "vec3.h"
#include "Log.hpp"

// In obj file :
// "v"  ----> vertex
// "vt" ----> texture coordinates
// "vn" ----> normal of a vertex
// "f"  ----> face 
// Example : f 8/11/7 
// 8 is the eight "v" (vertex) of the file
// 11 is the eleventh "vt" (texture coordinates) of the file
// 7 is the seventh "vn" (normal of a vertex) of the file

using namespace Resources;

Model::Model()
{

}

Model::Model(const char* fileName)
{
    load_obj(fileName);
}

Model::~Model()
{

}

void Model::clear_model_data()
{
    name.clear();
    vertices.clear();
    uvs.clear();
    normals.clear();
    loaded = false;
}

void Model::load_obj(const char* fileName)
{
    // open file
    std::ifstream file(fileName);
    if (Core::Debug::Log::is_file_opened(file, fileName) == false) { return; };

    // clear every std::vectors so we can parse a new .obj
    if (loaded)
        this->clear_model_data();

    this->name = fileName;

    // some vars
    std::string header;
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< Core::Maths::vec3 > temp_vertices;
    std::vector< Core::Maths::vec2 > temp_uvs;
    std::vector< Core::Maths::vec3 > temp_normals;
    
    // Read the file
    while(!file.eof())
    {
        file >> header;

        if      (header == "v")
            extract_obj_vertex(file, temp_vertices);
        else if (header == "vt")
            extract_obj_uv(file, temp_uvs);
        else if (header == "vn")
            extract_obj_normal(file, temp_normals);
        else if (header == "f")
            extract_obj_face(file, vertexIndices, uvIndices, normalIndices);
    }

    // Sort our raw data using indices
    for(unsigned int i = 0; i < vertexIndices.size(); ++i)
    {
        assert(vertexIndices[i] - 1 >= 0 && uvIndices[i] - 1 >= 0 && normalIndices[i] - 1 >= 0);
        this->vertices  .push_back(temp_vertices[ vertexIndices[i] - 1 ]);
        this->uvs       .push_back(temp_uvs     [ uvIndices[i] - 1 ]);
        this->normals   .push_back(temp_normals [ normalIndices[i] - 1]);
    }
    // create the final version of our vertices in order to put it in VBO
    this->create_convertedVertices();
    loaded = true;
}

void Model::extract_obj_face(std::ifstream& file, std::vector<unsigned int>& vertexIndices, std::vector<unsigned int>& uvIndices, std::vector<unsigned int>& normalIndices)
{
    // Reading a "f" line in the file, example : "f" 8/4/8 7/6/9 5/1/2
    // extract the line
    std::string line;
    std::getline(file, line);

    // count number of '/' in our line
    unsigned int nbSlashs = std::count(line.begin(), line.end(), '/');
    assert(nbSlashs / 2 > 0);
    unsigned int nbElements = nbSlashs / 2;

    // reset cursor pos
    file.seekg(line.size() * (-1), std::ifstream::cur);

    // extract data // iterator is just to go through the slashs
    unsigned char iterator;
    unsigned int vertexIndex[4], uvIndex[4], normalIndex[4];
    for (unsigned int i = 0; i < nbElements; ++i)
    {
        file >> vertexIndex[i] >> iterator >> uvIndex[i] >> iterator >> normalIndex[i];
        if (i <= 2)
        {
            vertexIndices.push_back(vertexIndex[i]);
            uvIndices    .push_back(uvIndex[i]);
            normalIndices.push_back(normalIndex[i]);
        }
        else if (i == 3)
        {
            vertexIndices.push_back(vertexIndex[0]);
            uvIndices    .push_back(uvIndex[0]);
            normalIndices.push_back(normalIndex[0]);

            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[2]);

            vertexIndices.push_back(vertexIndex[3]);
            uvIndices    .push_back(uvIndex[3]);
            normalIndices.push_back(normalIndex[3]);
        }
    }
}


std::vector<Core::Maths::vec3> Model::get_vertices()
{
    return vertices;
}

std::vector<Core::Maths::vec2> Model::get_uvs()
{
    return uvs;
}

std::vector<Core::Maths::vec3> Model::get_normals()
{
    return normals;
}

std::vector<float> Model::get_converted_vertices()
{
    return convertedVertices;
}

std::string Model::get_name()
{
    return name;
}

void Model::create_convertedVertices()
{
    // sort the whole data in just one array in order to put it in the VBO
    for (unsigned int i = 0; i < vertices.size(); ++i)
    {
        this->convertedVertices.push_back(this->vertices[i].x);
        this->convertedVertices.push_back(this->vertices[i].y);
        this->convertedVertices.push_back(this->vertices[i].z);

        this->convertedVertices.push_back(this->uvs[i].x);
        this->convertedVertices.push_back(this->uvs[i].y);

        this->convertedVertices.push_back(this->normals[i].x);
        this->convertedVertices.push_back(this->normals[i].y);
        this->convertedVertices.push_back(this->normals[i].z);
    }
}


void Model::extract_obj_vertex(std::ifstream& file, std::vector<Core::Maths::vec3>& temp_vertices)
{
    Core::Maths::vec3 vertex;
    file >> vertex.x >> vertex.y >> vertex.z;
    temp_vertices.push_back(vertex);
}


void Model::extract_obj_uv(std::ifstream& file, std::vector<Core::Maths::vec2>& temp_uvs)
{
    Core::Maths::vec2 uv;
    file >> uv.x >> uv.y;
    temp_uvs.push_back(uv);
}

void Model::extract_obj_normal(std::ifstream& file, std::vector<Core::Maths::vec3>& temp_normals)
{
    Core::Maths::vec3 normal;
    file >> normal.x >> normal.y >> normal.z;
    temp_normals.push_back(normal);
}

bool Model::is_loaded()
{
    return loaded;
}