#ifndef MEGENGINEPROJECT_PLAYER_CONTROLLER_H
#define MEGENGINEPROJECT_PLAYER_CONTROLLER_H

#include "MEGEngine/Common.hpp"
#include "MEGEngine/Core/Entity.hpp"
#include "MEGEngine/Platform/Input/InputReceiver.hpp"


class ENGINE_API PlayerController {
public:
    static PlayerController& instance();
    void possess(Entity& player);
    void update();
    InputReceiver* inputReceiver();

private:
    InputReceiver* _inputReceiver = nullptr;

};


#endif //MEGENGINEPROJECT_PLAYER_CONTROLLER_H