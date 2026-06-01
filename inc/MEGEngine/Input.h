#ifndef MEGENGINEPROJECT_INPUT_H
#define MEGENGINEPROJECT_INPUT_H

#include "MEGEngine/Input/input_action.h"
#include "MEGEngine/Input/input_context.h"
#include "MEGEngine/Input/input_device.h"
#include "MEGEngine/Input/input_events.h"
#include "MEGEngine/Input/input_manager.h"
#include "MEGEngine/Input/input_mapping.h"
#include "MEGEngine/Input/input_system.h"
#include "MEGEngine/Input/raw_input_event_bus.h"
#include "MEGEngine/Input/player_action_bus.h"
#include "MEGEngine/Input/input_receiver.h"
#include "MEGEngine/Core/window.h"

#include "MEGEngine/common.h"

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

void ENGINE_API setCursorPosition(Window& window, float x, float y);
void ENGINE_API setCursorPosition(Window& window, Vec2 pos);

Vec2 ENGINE_API getCursorPosition(Window& window, Vec2* pos);

void ENGINE_API setInputMode(Window& window, InputMode mode, InputModeValue value);
InputModeValue ENGINE_API getInputMode(Window& window, InputMode mode);

#endif //MEGENGINEPROJECT_INPUT_H