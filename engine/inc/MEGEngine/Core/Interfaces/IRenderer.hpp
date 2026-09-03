#ifndef MEGENGINE_IRENDERER_H
#define MEGENGINE_IRENDERER_H

#include "MEGEngine/Core/Scene.hpp"
#include "MEGEngine/Core/Entity.hpp"

class IRenderer {
public:
    virtual ~IRenderer() {};
    virtual bool init() = 0;
    virtual void render(const Scene& scene) = 0;

protected:
    virtual void draw(Entity& entity, const Scene& scene) = 0;
};

#endif