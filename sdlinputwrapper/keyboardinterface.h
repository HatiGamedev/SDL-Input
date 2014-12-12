#ifndef KEYBOARDINTERFACE_H
#define KEYBOARDINTERFACE_H

#include "sdli_definitions.h"
#include "util/indexmap.h"

namespace sdli {

class KeyboardInterface
{
    std::vector<RawInputData> perFrameCaptures;

    sdli::util::IndexMap<InputAxis, LogicAnalogData> logicAnalogData;
    sdli::util::IndexMap<InputAction, LogicDigitalData> captureBuffer;

public:
    KeyboardInterface(const int max_actions, const int max_axes);
    ~KeyboardInterface();

    void poll(sdli::Context& ctx);
    void push(unsigned int rawInput, int value);
    void dispatch(sdli::Context& ctx);

    float getRange(InputAxis axis);
    bool isPressed(InputAction action);
    bool isReleased(InputAction action);
    bool isDown(InputAction action);
    bool isUp(InputAction action);

    void swap();
};

} // sdli

#endif // KEYBOARDINTERFACE_H
