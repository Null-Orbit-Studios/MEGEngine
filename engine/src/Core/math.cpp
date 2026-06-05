#include "GLM/glm.hpp"
#include "MEGEngine/Math.h"

float radians(float deg) {
    return glm::radians(deg);
}

float degrees(float rad) {
    return glm::degrees(rad);
}

float clamp(float value, float min, float max) {
    return glm::clamp(value, min, max);
}
