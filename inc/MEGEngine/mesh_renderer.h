#ifndef MEGENGINEPROJECT_MESH_RENDERER_H
#define MEGENGINEPROJECT_MESH_RENDERER_H

#include <memory>

#include "MEGEngine/common.h"
#include "MEGEngine/component.h"

namespace MEGEngine {
    class ENGINE_API MeshRenderer : public Component {
    public:
        MeshRenderer(std::shared_ptr<class Mesh> mesh, std::shared_ptr<class Material> material);
        void setMaterial(std::shared_ptr<class Material> material);
        [[nodiscard]] std::shared_ptr<class Material> material() const;
        [[nodiscard]] std::shared_ptr<class Mesh> mesh() const;

    private:
        std::shared_ptr<class Mesh> _mesh;
        std::shared_ptr<class Material> _material;
    };
} // MEGEngine

#endif //MEGENGINEPROJECT_MESH_RENDERER_H