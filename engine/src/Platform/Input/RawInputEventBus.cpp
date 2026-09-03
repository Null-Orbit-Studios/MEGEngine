#include "MEGEngine/Platform/Input/RawInputEventBus.hpp"


std::vector<std::unique_ptr<Base_QueuedEvent>> RawInputEventBus::_eventQueue;

void RawInputEventBus::dispatch() {
    for (auto& event : _eventQueue)
        event->dispatch();

    _eventQueue.clear();
}

