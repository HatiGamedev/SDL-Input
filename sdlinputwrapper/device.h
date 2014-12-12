#ifndef DEVICE_H
#define DEVICE_H

#include <stack>
#include "sdli_definitions.h"

namespace sdli {

class Device
{
    sdli::Interface* interface {nullptr};
    sdli::KeyboardInterface* keyboardInterface {nullptr};

    std::stack<sdli::Context*> contextStack_;

    friend class Processor;

protected:
    void setInterface(sdli::Interface* interface);
    void setKeyboard(sdli::KeyboardInterface* keyboard);

public:
    Device();

    // Prevent user-copy, due to handle incoruption
    Device(const Device&) =delete;
    Device& operator=(const Device&) =delete;

    void pushContext(sdli::Context* ctx);
    sdli::Context* currentContext();
    sdli::Context* popContext();

    void poll();
    void dispatch();


    float getAxis(InputAxis axis);
    bool isPressed(InputAction action);
    bool isReleased(InputAction action);
    bool isDown(InputAction action);
    bool isUp(InputAction action);

    void swap();
};

} // sdli

#endif // DEVICE_H
