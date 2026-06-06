#include "GLAD/glad.h"
// #include "GLFW/glfw3.h"

#include "MEGEngine/Renderer/OpenGLRenderer.h"
#include "MEGEngine/Core/camera.h"
#include "MEGEngine/Renderer/material.h"
#include "MEGEngine/Renderer/mesh.h"
#include "MEGEngine/Renderer/mesh_renderer.h"
#include "MEGEngine/Renderer/shader.h"
#include "MEGEngine/Core/scene.h"
#include "MEGEngine/Renderer/texture.h"

#include "MEGEngine/Math/glm_conversions.h"

#include "MEGEngine/Utils/log.h"


struct OpenGLRenderer::RenderGroup {
    Shader* shader = nullptr;
    std::vector<Entity*> entities;
};

bool OpenGLRenderer::init() {
    int status = gladLoadGL();
    if (!status) { return false; }

	glViewport(0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    _initialised = true;

    return true;
}

void OpenGLRenderer::render(const Scene& scene) {
    if (!_initialised)
        return;

    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<RenderGroup> renderQueue;

    for (auto& entity : scene.entities()) {
        if (entity->hasComponent<MeshRenderer>()) { // loop through render groups to store entities in order of shader
            if (renderQueue.empty()) {
                RenderGroup newGroup;
                newGroup.shader = entity->getComponent<MeshRenderer>()->material()->shader();
                renderQueue.push_back(newGroup);
            }

            for (size_t i = 0; i < renderQueue.size(); i++) {
                if (entity->getComponent<MeshRenderer>()->material()->shader()->ID() == renderQueue[i].shader->ID()) {
                    renderQueue[i].entities.push_back(entity.get());
                }
                else if (i == renderQueue.size() - 1) {
                    RenderGroup newGroup;
                    newGroup.shader = entity->getComponent<MeshRenderer>()->material()->shader();
                    newGroup.entities.push_back(entity.get());
                    renderQueue.push_back(newGroup);
                }
            }
        }
    }

    for (RenderGroup& group : renderQueue) {
        glUseProgram(group.shader->ID());
        for (auto entity : group.entities) {
            draw(*entity, scene);
        }
    }
}

void OpenGLRenderer::draw(Entity& entity, const Scene& scene) {
    auto mr = entity.getComponent<MeshRenderer>();

    if (!mr->material()->shader()) {
        Log(LogLevel::WRN, "Attempt to draw failed. Shader is null");
        return;
    }

    mr->material()->bind();
    mr->mesh()->bind();

    // Keep track of how many of each type of textures we have
    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    // for (unsigned int i = 0; i < entity.meshRenderer()->material()->textures().size(); i++)
    unsigned int slot = 0;
    for (auto& pair : mr->material()->textures())
    {
        TexType type = pair.first;
        std::shared_ptr<Texture> texture = pair.second;
        std::string num;
        std::string uniformName;
        if (type == TexType::ALBEDO) // TODO: add support for other texture types
        {
            num = std::to_string(numDiffuse++);
            uniformName = "diffuse" + num;
        }
        else if (type == TexType::SPECULAR)
        {
            num = std::to_string(numSpecular++);
            uniformName = "specular" + num;
        }
        texture->texUnit(*mr->material()->shader(), (uniformName).c_str(), slot++);
        texture->bind();
    }
    mr->material()->shader()->setUniform("camPos", scene.camera().getComponent<Transform>()->position());
    mr->material()->shader()->setUniform("camMatrix", scene.camera().camMatrix());

    // Create matrices
    Mat4 trans = Mat4::translation(entity.getComponent<Transform>()->position());
    Mat4 rot = entity.getComponent<Transform>()->orientation().toMatrix();
    Mat4 sca = Mat4::scale(entity.getComponent<Transform>()->scale());

    // Push the matrices to the vertex shader
    Mat4 modelMatrix = entity.getComponent<Transform>()->modelMatrix();
    mr->material()->shader()->setUniform("model",  modelMatrix);
    mr->material()->shader()->setUniform("translation", trans);
    mr->material()->shader()->setUniform("rotation", rot);
    mr->material()->shader()->setUniform("scale", sca);

    // TODO: shader support for multiple light sources
    mr->material()->shader()->setUniform("lightData", scene.lightData()[0]);
    
    // if this entity is the light, set its translation in vert shader
    auto* light = dynamic_cast<Light*>(&entity);
    if (light) {
        mr->material()->shader()->setUniform("translation", Mat4::translation(scene.lightData()[0].position));
    }

    // Draw the actual mesh
    glDrawElements(GL_TRIANGLES, mr->mesh()->numIndices(), GL_UNSIGNED_INT, 0);
}
