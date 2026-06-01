#include "GLAD/glad.h"
#include "GLM/gtc/type_ptr.hpp"
#include "GLM/gtx/rotate_vector.hpp"
#include "GLM/gtx/vector_angle.hpp"

#include "MEGEngine/camera.h"
#include "MEGEngine/window.h"
#include "MEGEngine/timer.h"

#include "MEGEngine/Math/glm_conversions.h"

#include "MEGEngine/engine.h"

#include "MEGEngine/Utils/log.h"


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
