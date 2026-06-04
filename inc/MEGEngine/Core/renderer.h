#ifndef MEGENGINEPROJECT_RENDERER_H
#define MEGENGINEPROJECT_RENDERER_H

#include <memory>
#include <vector>

#include "MEGEngine/common.h"
#include "Interfaces/IRenderer.h"


class ENGINE_API Renderer : public IRenderer {
public:
    Renderer() {};
    ~Renderer() override = default;

    void init() override;
    void render(const Scene& scene) override;

private:
    void draw(Entity& entity, const Scene& scene) override;

    bool _initialised = false;
    struct RenderGroup;
};


#endif //MEGENGINEPROJECT_RENDERER_H