#include "gmock/gmock.h"

#include "MEGEngine/Core/Light.hpp"

class Light_mock : public Light {
    MOCK_METHOD1(setType, void(LightType));
    MOCK_METHOD0(type, LightType());

    MOCK_METHOD1(setColour, void(const Colour&));
    MOCK_METHOD1(setIntensity, void(float));

    MOCK_METHOD0(colour, Colour());
    MOCK_METHOD0(intensity, float());

    MOCK_CONST_METHOD0(isDirty, bool());
    MOCK_METHOD0(clearDirty, void());
};