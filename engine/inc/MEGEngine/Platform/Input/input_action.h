#ifndef MEGENGINEPROJECT_INPUT_ACTION_H
#define MEGENGINEPROJECT_INPUT_ACTION_H

#include <string>
#include <variant>

#include "MEGEngine/common.h"
#include "MEGEngine/Math/vec2.h"

#include "MEGEngine/Platform/Input/player_action_bus.h"
#include "MEGEngine/Platform/Input/input_events.h"


class ENGINE_API ActionValue {
public:
    using variant = std::variant<bool, float, Vec2>;

    ActionValue() : _value(false) {}
    ActionValue(bool v) : _value(v) {}
    ActionValue(float v) : _value(v) {}
    ActionValue(int v) : _value(float(v)) {}
    ActionValue(Vec2 v) : _value(v) {}

    bool asBool() const {
        const bool* val = std::get_if<bool>(&_value);
        if (val)
            return *val;
        else
            return false;
    }

    float asFloat() const {
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

    /**
     * @brief Get the current value of the action
     * 
     * If the action has multiple inputs (i.e. movement actions), the sum of
     * the values for these actions is returned. Otherwise, the standalone value
     * of the action is returned.
     * 
     * @return ```ActionValue```
     */
    ActionValue value() const {
        if(_valueMap.empty()) {
            return false;
        }

        const bool* boolVal = std::get_if<bool>(&_valueMap.begin()->second.asVariant());
        if (boolVal) {
            bool totalValue = false;
            for (auto pair : _valueMap) {
                totalValue += pair.second.asBool();
            }
            return totalValue;
        }

        const float* floatVal = std::get_if<float>(&_valueMap.begin()->second.asVariant());
        if (floatVal) {
            float totalValue = 0.0f;
            for (auto pair : _valueMap) {
                totalValue += pair.second.asFloat();
            }
            return totalValue;
        }

        const Vec2* vecVal = std::get_if<Vec2>(&_valueMap.begin()->second.asVariant());
        if (vecVal) {
            Vec2 totalValue = {0, 0};
            for (auto pair : _valueMap) {
                totalValue += pair.second.asVec2();
            }
            return totalValue;
        }

        return false;
    }

    /**
     * @brief Add to the value of the state.
     * 
     * If the key is ```KeyCode::UNKNOWN``` then the action is not key-press related
     * (i.e. mouse delta). Value is set as the ```val``` parameter. Otherwise, ```val```
     * is added to a map of values.
     * 
     * @param [in] KeyCode  Enum of the key that has been pressed or released
     * @param [in] ActionValue The value of the action. 
     */
    void addValue(KeyCode key, ActionValue val) {
        if (hasValue(key)) {
            _valueMap[key] = val;
            return;
        }
        _valueMap.emplace(key, val);
    }

    void removeValue(KeyCode key) {
        _valueMap.erase(key);
    }

    bool hasValue(KeyCode key) {
        return (_valueMap.find(key) != _valueMap.end());
    }

    bool valueIsEmpty() {
        return _valueMap.empty();
    }

    bool started = false;
    bool ongoing = false;
    bool completed = false;

private:
    std::unordered_map<KeyCode, ActionValue> _valueMap;
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


struct ENGINE_API ActionCallback {
    InputAction* action;
    PlayerActionBus::Callback callback;
};


#endif //MEGENGINEPROJECT_INPUT_ACTION_H