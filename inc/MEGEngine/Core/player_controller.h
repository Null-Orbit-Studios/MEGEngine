#ifndef MEGENGINEPROJECT_PLAYER_CONTROLLER_H
#define MEGENGINEPROJECT_PLAYER_CONTROLLER_H

#include "MEGEngine/common.h"
#include "MEGEngine/Core/entity.h"
#include "MEGEngine/Input/input_receiver.h"


class ENGINE_API PlayerController {
public:
    void possess(Entity& player);
    void update();
    InputReceiver* inputReceiver();

private:
    InputReceiver* _inputReceiver = nullptr;

};


#endif //MEGENGINEPROJECT_PLAYER_CONTROLLER_H