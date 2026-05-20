#ifndef MEGENGINEPROJECT_PLAYER_CONTROLLER_H
#define MEGENGINEPROJECT_PLAYER_CONTROLLER_H

#include "MEGEngine/common.h"
#include "MEGEngine/entity.h"
#include "MEGEngine/input/input_receiver.h"

namespace MEGEngine {
    class ENGINE_API PlayerController {
    public:
        void possess(Entity& player);
        void update();
        InputReceiver* inputReceiver();

    private:
        InputReceiver* _inputReceiver = nullptr;

    };
} // MEGEngine

#endif //MEGENGINEPROJECT_PLAYER_CONTROLLER_H