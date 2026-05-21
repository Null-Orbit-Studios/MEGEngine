#include "MEGEngine.h"
#include "MEGEngine/timer.h"
#include "MEGEngine/Math.h"

class MoveCamera : public ScriptedBehaviour {
public:

    MoveCamera() = default;

    void onStart() override {
        MEGEngine::Log(LogLevel::DBG, "MoveCamera onStart()");
    }

    void onUpdate() override {
        if (_localMove.length() * _localMove.length() > 0) {
            _localMove = _localMove.normalized();

            MEGEngine::Vec3 worldMove = parent()->getComponent<MEGEngine::Transform>()->orientation().rotate(_localMove);
            parent()->getComponent<MEGEngine::Transform>()->setPosition(parent()->getComponent<MEGEngine::Transform>()->position() + (worldMove * speed * MEGEngine::Timer::deltaTime()));
        }

        _localMove = {0, 0, 0};
    }

    void moveForward(float val) {
        if (val)
            _localMove.z += val;
    }
    void moveRight(float val) {
        if (val)
            _localMove.x += val;
    }


private:
        float speed = 5.0f;
		float baseSpeed = 5.0f;
		bool isSprinting = false;
		float boostSpeed = 10.0f;

        MEGEngine::Vec3 _localMove = {0, 0, 0};
};