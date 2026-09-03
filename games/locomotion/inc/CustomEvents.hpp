#ifndef CUSTOMEVENTS_H
#define CUSTOMEVENTS_H

#include "MEGEngine/Core/Events.hpp"
#include "MEGEngine/Utils/Logger.hpp"

class TestEvent : public Event {};
class TestEventListener : public EventListener {
public:
    TestEventListener(Entity& parent) : EventListener(parent) {}

    void onEvent() override {
        LOG_DBG("Test Event Listener received trigger");
    }
};

#endif //CUSTOMEVENTS_H