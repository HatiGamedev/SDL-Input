#ifndef MOUSEINTERFACE_H
#define MOUSEINTERFACE_H

#include "sdli_definitions.h"
#include "util/indexmap.h"

namespace sdli {

class MouseInterface
{
    std::vector<RawInputData> perFrameCaptures;

    sdli::util::IndexMap<InputAxis, LogicAnalogData> logicAnalogData;
    sdli::util::IndexMap<InputAction, LogicDigitalData> captureBuffer;

public:
    MouseInterface(const int max_actions);
    ~MouseInterface();

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

#endif // MOUSEINTERFACE_H
