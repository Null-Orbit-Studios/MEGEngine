#ifndef MEGENGINEPROJECT_TRANSFORM_H
#define MEGENGINEPROJECT_TRANSFORM_H


#include "MEGEngine/Common.hpp"
#include "MEGEngine/Core/Component.hpp"

#include "MEGEngine/Math/Quat.hpp"
#include "MEGEngine/Math/Mat4.hpp"
#include "MEGEngine/Math/Vec3.hpp"


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