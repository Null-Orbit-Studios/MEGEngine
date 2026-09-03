#ifndef SCRIPTED_BEHAVIOUR_H
#define SCRIPTED_BEHAVIOUR_H

#include "MEGEngine/Common.hpp"

class ENGINE_API ScriptedBehaviour : public Component {
public:
    virtual void onStart() {}; // called when entity owning script is instantiated
    virtual void onUpdate() {}; // called each frame
};

#endif