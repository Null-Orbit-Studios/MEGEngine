#ifndef MEGENGINE_VULKAN_RENDERER_H
#define MEGENGINE_VULKAN_RENDERER_H

#include "MEGEngine/Core/Interfaces/IRenderer.hpp"

class VulkanRenderer : public IRenderer {
public:
    VulkanRenderer() {};
    ~VulkanRenderer() override = default;

    /**
     * @brief Initialises the renderer
     * 
     * Initialises the renderer using a Vulkan backend
     * 
     * @returns uint32_t indicating success (0) or error (!0)
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

};

#endif