#ifndef CUSTOMEVENTS_H
#define CUSTOMEVENTS_H

#include "MEGEngine/events.h"
#include "MEGEngine/utils/log.h"

class TestEvent : public Event {};
class TestEventListener : public EventListener {
public:
    TestEventListener(Entity& parent) : EventListener(parent) {}

    void onEvent() override {
        Log(LogLevel::DBG, "Test Event Listener received trigger");
    }
};

#endif //CUSTOMEVENTS_H