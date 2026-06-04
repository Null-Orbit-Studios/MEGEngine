#ifndef MEGENGINEPROJECT_RENDERER_H
#define MEGENGINEPROJECT_RENDERER_H

#include <memory>
#include <vector>

#include "MEGEngine/common.h"
#include "Interfaces/IRenderer.h"


class ENGINE_API OpenGLRenderer : public IRenderer {
public:
    OpenGLRenderer() {};
    ~OpenGLRenderer() override = default;

    /**
     * @brief Initialises the renderer
     * 
     * Initialises the renderer using an OpenGL GLAD backend
     * 
     * @returns void
     */
    void init() override;

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
    struct RenderGroup;
};


#endif //MEGENGINEPROJECT_RENDERER_H