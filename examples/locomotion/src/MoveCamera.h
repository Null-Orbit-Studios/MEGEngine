#include <cmath>

#include "MEGEngine.h"
#include "MEGEngine/Core/timer.h"
#include "MEGEngine/Math.h"
#include "MEGEngine/Core/application.h"

class MoveCamera : public ScriptedBehaviour {
public:

    MoveCamera() = default;

    void onStart() override {
        Log(LogLevel::DBG, "MoveCamera onStart()");
    }

    void onUpdate() override {
        if (_localMove.length() * _localMove.length() > 0) {
            _localMove = _localMove.normalized();

            Vec3 worldMove = parent()->getComponent<Transform>()->orientation().rotate(_localMove);
            parent()->getComponent<Transform>()->setPosition(parent()->getComponent<Transform>()->position() + (worldMove * speed * Timer::deltaTime()));
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

    void look(Vec2 val) {
        if (getInputMode(Engine::instance().application().window(), InputMode::CURSOR) != InputModeValue::CURSOR_DISABLED) return;

        float rotX = sensitivity * 0.5 * val.y;
        float rotY = sensitivity * 0.5 * val.x;

        Quat tmpOrientation = parent()->getComponent<Transform>()->orientation();

        Vec3 camRight = parent()->getComponent<Transform>()->orientation().rotate(Vec3::worldRight());
        Quat pitch = Quat::fromAxisAngle(camRight, radians(rotX));
        tmpOrientation = pitch * tmpOrientation;

        Vec3 camForward = tmpOrientation.rotate(Vec3::worldForward());
        float pitchAngle = degrees(std::asin(clamp(camForward.y, -1.0f, 1.0f)));

        // Decides whether or not the next vertical Orientation is legal or not
        if (pitchAngle > -85.0f && pitchAngle < 85.0f)
        {
            parent()->getComponent<Transform>()->setOrientation(tmpOrientation);
        }

        // Rotates the Orientation left and right
        Quat yaw = Quat::fromAxisAngle(Vec3::worldUp(), radians(rotY));
        parent()->getComponent<Transform>()->setOrientation(yaw * parent()->getComponent<Transform>()->orientation().normalised());
    }


private:
        float speed = 5.0f;
		float baseSpeed = 5.0f;
		bool isSprinting = false;
		float boostSpeed = 10.0f;
        Vec3 _localMove = {0, 0, 0};

        float sensitivity = 1.0f;

        bool cursorCaptured = false;
};