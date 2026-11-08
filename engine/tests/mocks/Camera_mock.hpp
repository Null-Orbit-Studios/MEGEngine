#include "gmock/gmock.h"

#include "MEGEngine/Core/Camera.hpp"

class Camera_mock : public Camera {
    MOCK_METHOD0(updateCamMatrix, void());
    MOCK_METHOD0(camMatrix, Mat4());
};