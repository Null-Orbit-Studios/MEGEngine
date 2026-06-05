#ifndef MEGENGINEPROJECT_TRANSFORM_H
#define MEGENGINEPROJECT_TRANSFORM_H


#include "MEGEngine/common.h"
#include "MEGEngine/Core/component.h"

#include "MEGEngine/Math/quat.h"
#include "MEGEngine/Math/mat4.h"
#include "MEGEngine/Math/vec3.h"


class ENGINE_API Transform : public Component {
public:
    Transform();

    void setPosition(const Vec3& position);
    void setOrientation(const Quat& orientation);
    void setScale(const Vec3& scale);
    void setScale(float scale);

    Vec3 position() const;
    Quat orientation() const;
    Vec3 scale() const;

    Mat4 modelMatrix() const;

private:
    Vec3 _position = Vec3(0, 0, 0);
    Quat _orientation = Quat::identity();
    Vec3 _scale = Vec3(1, 1, 1);
};


#endif //MEGENGINEPROJECT_TRANSFORM_H