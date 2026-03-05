#ifndef MEGENGINEPROJECT_COMPONENT_H
#define MEGENGINEPROJECT_COMPONENT_H

#include <typeindex>

#include "MEGEngine/common.h"

namespace MEGEngine {
    // Abstract class - serves as the base class for all entity components
    class ENGINE_API Component {
    protected:
        Component() = default;
    };

    using ComponentTypeID = std::type_index;
} // MEGEngine

#endif //MEGENGINEPROJECT_COMPONENT_H