#include <iostream>

#include "ResourcesManager.hpp"
#include "Model.hpp"
#include "Texture.hpp"

using namespace Resources;

ResourcesManager::ResourcesManager()
{

}

ResourcesManager::~ResourcesManager()
{
    
}


LowRenderer::Mesh ResourcesManager::load_mesh(const char* objFileName, const char* texFileName)
{
    LowRenderer::Mesh askedMesh;

    // looking for asked model
    for (std::vector<Model>::iterator it = models.begin(); it != models.end(); ++it)
    {
        if (it->get_name() == objFileName)
            askedMesh.model = *it;
    }
    // looking for asked texture
    for (std::vector<Texture>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        if (it->get_name() == texFileName)
            askedMesh.texture = *it;
    }

    // if model or texture not found, add it to the resourcesManager and return askedMesh
    if (!askedMesh.model.is_loaded())
    {
        std::cout << "IN1" << std::endl;
        askedMesh.model = Model(objFileName);
        this->models.push_back(askedMesh.model);
    }
    if (!askedMesh.texture.is_loaded())
    {
        std::cout << "IN2" << std::endl;
        askedMesh.texture = Texture(texFileName);
        this->textures.push_back(askedMesh.texture);
    }

    askedMesh.load_buffers();
    return askedMesh;
}