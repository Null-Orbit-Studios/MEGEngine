#ifndef MEGENGINEPROJECT_LIGHT_H
#define MEGENGINEPROJECT_LIGHT_H


#include "MEGEngine/common.h"
#include "MEGEngine/Core/colour.h"
#include "MEGEngine/Core/entity.h"



enum class LightType {
    POINT_LIGHT = 0,
    SPOT_LIGHT,
    DIRECTIONAL_LIGHT,
};

struct ENGINE_API LightData {
    Vec3 position;
    Colour colour;
    float intensity;
    LightType type;
};

class ENGINE_API Light : public Entity {
public:
    void setType(LightType type);
    LightType type();

    void setColour(const Colour& colour);
    void setIntensity(float intensity);

    Colour colour();
    float intensity();

    bool isDirty() const;
    void clearDirty();
protected:
    Colour _colour = {1.0f, 1.0f, 1.0f, 1.0f};
    float _intensity = 1.0f;
    bool _dirty = true;
    LightType _type = LightType::POINT_LIGHT;
};


#endif //MEGENGINEPROJECT_LIGHT_H