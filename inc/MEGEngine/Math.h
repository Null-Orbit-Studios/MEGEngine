#ifndef MEGENGINEPROJECT_MATH_H
#define MEGENGINEPROJECT_MATH_H

#include "MEGEngine/math/mat4.h"
#include "MEGEngine/math/vec4.h"
#include "MEGEngine/math/vec3.h"
#include "MEGEngine/math/vec2.h"
#include "MEGEngine/math/quat.h"

// free floating functions that don't belong to any class
float ENGINE_API radians(float deg);
float ENGINE_API degrees(float rad);

float ENGINE_API clamp(float value, float min, float max);

#endif //MEGENGINEPROJECT_MATH_H