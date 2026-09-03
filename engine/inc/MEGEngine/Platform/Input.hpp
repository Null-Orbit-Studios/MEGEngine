#ifndef MEGENGINEPROJECT_INPUT_H
#define MEGENGINEPROJECT_INPUT_H

#include "Input/InputAction.hpp"
#include "Input/InputContext.hpp"
#include "Input/InputDevice.hpp"
#include "Input/InputEvents.hpp"
#include "Input/InputManager.hpp"
#include "Input/InputMapping.hpp"
#include "Input/InputSystem.hpp"
#include "Input/RawInputEventBus.hpp"
#include "Input/PlayerActionBus.hpp"
#include "Input/InputReceiver.hpp"
#include "Window.hpp"

#include "MEGEngine/Common.hpp"

enum class InputMode {
    CURSOR,
    STICKY_KEYS,
    STICKY_MOUSE_BUTTONS,
    LOCK_KEY_MODS,
    RAW_MOUSE_MOTION
};

enum class InputModeValue {
    CURSOR_NORMAL,
    CURSOR_HIDDEN,
    CURSOR_DISABLED,
    CURSOR_CAPTURED,
    FALSE,
    TRUE,
    VOID
};

void ENGINE_API setCursorPosition(IWindow& window, float x, float y);
void ENGINE_API setCursorPosition(IWindow& window, Vec2 pos);

Vec2 ENGINE_API getCursorPosition(IWindow& window, Vec2* pos);

void ENGINE_API setInputMode(IWindow& window, InputMode mode, InputModeValue value);
InputModeValue ENGINE_API getInputMode(IWindow& window, InputMode mode);

#endif //MEGENGINEPROJECT_INPUT_H