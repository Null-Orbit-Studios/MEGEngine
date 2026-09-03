#include "MEGEngine/Core/Camera.hpp"
#include "MEGEngine/Platform/Window.hpp"
#include "MEGEngine/Core/Timer.hpp"
#include "MEGEngine/Core/Engine.hpp"

#include "MEGEngine/Math/GLMConversions.hpp"


#include "MEGEngine/Utils/Logger.hpp"


Camera::Camera(int width, int height) :
    _width(static_cast<float>(width)),
    _height(static_cast<float>(height)),
    _fov(75.0f),
    _nearZ(0.1f),
    _farZ(1000.0f){}

void Camera::updateCamMatrix() {
    Vec3 camForward = this->getComponent<Transform>()->orientation().rotate(Vec3::worldForward());
    Mat4 view = Mat4::lookAt(
        this->getComponent<Transform>()->position(),
        this->getComponent<Transform>()->position() + camForward,
        Vec3::worldUp()
        );

    Mat4 projection = Mat4::perspective(_fov, _width/_height, _nearZ, _farZ);

    _camMatrix = projection * view;
}

Mat4 Camera::camMatrix() const {
    return _camMatrix;
}
