#ifndef MEGENGINEPROJECT_INPUT_ACTION_H
#define MEGENGINEPROJECT_INPUT_ACTION_H

#include <string>
#include <variant>

#include "MEGEngine/common.h"
#include "MEGEngine/Math/vec2.h"


class ENGINE_API ActionValue {
public:
    using variant = std::variant<bool, float, Vec2>;

    ActionValue() : _value(false) {}
    ActionValue(bool v) : _value(v) {}
    ActionValue(float v) : _value(v) {}
    ActionValue(int v) : _value(float(v)) {}
    ActionValue(Vec2 v) : _value(v) {}

    const bool asBool() const {
        const bool* val = std::get_if<bool>(&_value);
        if (val)
            return *val;
        else
            return false;
    }

    const float asFloat() const {
        const float* val = std::get_if<float>(&_value);
        if (val)
            return *val;
        else
            return 0;
    }

    const Vec2 asVec2() const {
        const Vec2* val = std::get_if<Vec2>(&_value);
        if (val)
            return *val;
        else
            return Vec2(0, 0);
    }

    const variant& asVariant() const { return _value; }

private:
    variant _value;
};

struct ENGINE_API ActionState {
    ActionValue value;

    bool started = false;
    bool ongoing = false;
    bool completed = false;
};

class ENGINE_API InputAction {
public:
    enum class Type {
        BOOL,
        FLOAT,
        VEC2
    };

    InputAction(std::string name, Type type) : _name(std::move(name)), _type(type) {}

    std::string name() const { return _name; }
    Type type() const {return _type; }

private:
    std::string _name;
    Type _type;
};


#endif //MEGENGINEPROJECT_INPUT_ACTION_H