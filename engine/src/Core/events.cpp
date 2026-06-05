#include "MEGEngine/Core/events.h"
#include "MEGEngine/Core/timer.h"


EventListener::EventListener(Entity& parent) : _parent(parent) {}

Entity& EventListener::parent() {
    return _parent;
}

void EventManager::processEvents() {
    for (const auto& eventType: _eventQueue) {
        auto foundEvent = _listeners[eventType];
        for (EventListener* listener: foundEvent) {
            listener->onEvent();
        }
    }
    _eventQueue.clear();
}
