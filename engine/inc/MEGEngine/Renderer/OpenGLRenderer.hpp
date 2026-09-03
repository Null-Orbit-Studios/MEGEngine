#ifndef MEGENGINEPROJECT_RENDERER_H
#define MEGENGINEPROJECT_RENDERER_H

#include <memory>
#include <vector>

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Core/Interfaces/IRenderer.hpp"


class ENGINE_API OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer(int width, int height) : _width(width), _height(height) {};
    ~OpenGLRenderer() override = default;

    /**
     * @brief Initialises the renderer
     * 
     * Initialises the renderer using an OpenGL GLAD backend
     * 
     * @returns bool indicating success (True) or error (False)
     */
    bool init() override;

    /**
     * @brief Renders the scene on the screen
     * 
     * Sorts and groups the entities in a scene by the shaders they use
     * to minimise shader switching. After grouping, each group is then
     * drawn to the screen.
     * 
     * @returns void
     */
    void render(const Scene& scene) override;

private:
    void draw(Entity& entity, const Scene& scene) override;

    bool _initialised = false;
    int _width;
    int _height;
    struct RenderGroup;
};


#endif //MEGENGINEPROJECT_RENDERER_H