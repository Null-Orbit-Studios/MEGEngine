#ifndef MEGENGINEPROJECT_INPUT_H
#define MEGENGINEPROJECT_INPUT_H

#include "MEGEngine/input/input_action.h"
#include "MEGEngine/input/input_context.h"
#include "MEGEngine/input/input_device.h"
#include "MEGEngine/input/input_events.h"
#include "MEGEngine/input/input_manager.h"
#include "MEGEngine/input/input_mapping.h"
#include "MEGEngine/input/input_system.h"
#include "MEGEngine/input/raw_input_event_bus.h"
#include "MEGEngine/input/player_action_bus.h"
#include "MEGEngine/input/input_receiver.h"
#include "MEGEngine/window.h"

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