#ifndef MEGENGINEPROJECT_PLAYER_CONTROLLER_H
#define MEGENGINEPROJECT_PLAYER_CONTROLLER_H


#include "MEGEngine/common.h"
#include "MEGEngine/input/input_receiver.h"

namespace MEGEngine {
    class ENGINE_API PlayerController {
    public:
        void setInputReceiver(InputReceiver* receiver);

    private:
        InputReceiver* inputReceiver = nullptr;

    };
} // MEGEngine

#endif //MEGENGINEPROJECT_PLAYER_CONTROLLER_H