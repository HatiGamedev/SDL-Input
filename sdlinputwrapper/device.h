#ifndef DEVICE_H
#define DEVICE_H

#include <stack>
#include "sdli_definitions.h"

namespace sdli {

class Device
{
    sdli::Interface* interface {nullptr};
    std::stack<sdli::Context*> contextStack_;

public:
    Device(sdli::Interface* interface);

    // Prevent copy
    Device(const Device&) =delete;
    Device& operator=(const Device&) =delete;

    void pushContext(sdli::Context* ctx);
    sdli::Context* popContext();

    void poll();
    void dispatch();


    float getRange(InputAxis axis);
    bool isPressed(InputAction action);
    bool isReleased(InputAction action);
    bool isDown(InputAction action);
    bool isUp(InputAction action);
};

} // sdli

#endif // DEVICE_H
