#ifndef MEGENGINEPROJECT_COMPONENT_H
#define MEGENGINEPROJECT_COMPONENT_H
#include <typeindex>

namespace MEGEngine {
    // Abstract class - serves as the base class for all entity components
    class Component {
    public:
        virtual ~Component() = 0;
    };

    using ComponentTypeID = std::type_index;
} // MEGEngine

#endif //MEGENGINEPROJECT_COMPONENT_H