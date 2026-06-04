#ifndef MEGENGINE_IRENDERER_H
#define MEGENGINE_IRENDERER_H

#include "MEGEngine/Core/scene.h"
#include "MEGEngine/Core/entity.h"

class IRenderer {
public:
    virtual ~IRenderer() {};
    virtual bool init() = 0;
    virtual void render(const Scene& scene) = 0;

protected:
    virtual void draw(Entity& entity, const Scene& scene) = 0;
};

#endif