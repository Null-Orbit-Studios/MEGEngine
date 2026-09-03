#ifndef MEGENGINEPROJECT_MATH_H
#define MEGENGINEPROJECT_MATH_H

#include "MEGEngine/Math/Mat4.hpp"
#include "MEGEngine/Math/Vec4.hpp"
#include "MEGEngine/Math/Vec3.hpp"
#include "MEGEngine/Math/Vec2.hpp"
#include "MEGEngine/Math/Quat.hpp"

// free floating functions that don't belong to any class
float ENGINE_API radians(float deg);
float ENGINE_API degrees(float rad);

float ENGINE_API clamp(float value, float min, float max);

#endif //MEGENGINEPROJECT_MATH_H