#include <iostream>

#include "Mesh.hpp"
#include "Model.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "vec3.h"

using namespace LowRenderer;

Mesh::Mesh()
{

}

Mesh::Mesh(const char* objFileName, const char* texFileName)
{
    model.load_obj(objFileName);
    texture.load_texture(texFileName);
    this->load_buffers();
}

Mesh::~Mesh()
{

}

void Mesh::load_buffers()
{
    // Setup buffers
    glGenBuffers(1, &VBO);  
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // load VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->model.get_converted_vertices().size(), this->model.get_converted_vertices().data(), GL_STATIC_DRAW);

    // Vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::draw(Camera& camera)
{
    this->update(camera);
    // bind
    //this->shader.use_program();
    glBindVertexArray(this->VAO);
    this->texture.bind();
    // draw
    glDrawArrays(GL_TRIANGLES, 0, this->model.get_vertices().size());
    // unbind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Mesh::update(Camera& camera)
{
    // transform matrix
    Core::Maths::mat4 matTRS = transform.create_transform_matrix();
    //camera.matCam.transpose();
    Core::Maths::mat4 matCamTrs = (camera.matCam * matTRS);
    Core::Maths::mat4 matProjTRS = camera.matPerspective * matCamTrs;

    // apply matTransform to shader
    unsigned int transformLoc = glGetUniformLocation(this->shader.shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, matProjTRS.array.data());
}


void Mesh::draw(Camera& camera, Core::Maths::mat4& parentMatTRS, LowRenderer::Light& light)
{
    Core::Maths::mat4 matTRS    = transform.create_transform_matrix();
    Core::Maths::mat4 newMatTRS = parentMatTRS * matTRS;

    // drawing
    this->update(camera, newMatTRS, light);
    // bind
    //this->shader.use_program();
    glBindVertexArray(this->VAO);
    this->texture.bind();
    // draw
    glDrawArrays(GL_TRIANGLES, 0, this->model.get_vertices().size());
    // unbind
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Mesh::update(Camera& camera, Core::Maths::mat4& parentMatTRS, LowRenderer::Light& light)
{
    Core::Maths::mat4 matCamTrs = (camera.matCam * parentMatTRS);
    Core::Maths::mat4 matProjTRS = camera.matPerspective * matCamTrs;

    // apply matTransform to shader
    // vertexShader
    unsigned int cameraLoc = glGetUniformLocation(this->shader.shaderProgram, "camera");
    glUniformMatrix4fv(cameraLoc, 1, GL_TRUE, camera.matCam.array.data());

    unsigned int projLoc   = glGetUniformLocation(this->shader.shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_TRUE, camera.matPerspective.array.data());

    unsigned int transformLoc = glGetUniformLocation(this->shader.shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_TRUE, parentMatTRS.array.data());

    // fragmentShader
    light.apply(shader);
    unsigned int viewPosLoc = glGetUniformLocation(this->shader.shaderProgram, "viewPos");
    glUniform3f(viewPosLoc, camera.posCam.x, camera.posCam.y, camera.posCam.z);
}