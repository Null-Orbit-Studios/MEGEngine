#ifndef MEGENGINEPROJECT_COMPONENT_H
#define MEGENGINEPROJECT_COMPONENT_H

#include <typeindex>

#include "MEGEngine/Common.hpp"


class Entity; // forward declared to avoid circular dependency

// Base class for all entity components
class ENGINE_API Component {
public:
    virtual ~Component() = default;

    Entity* parent() const {
        return _parent;
    }

private:
    friend class Entity;
    Entity* _parent = nullptr;
};

using ComponentTypeID = std::type_index;


#endif //MEGENGINEPROJECT_COMPONENT_H