#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <map>
#include <vector>

#include "sdli_definitions.h"
#include <stack>
#include <functional>

#include "data/framestate.cpp"
#include "util/array.h"
#include "util/indexmap.h"

namespace sdli {

class Interface
{
private:
    std::vector<RawInputData> perFrameCaptures;

    sdli::util::IndexMap<InputAxis, LogicAnalogData> logicAnalogData;

    sdli::util::IndexMap<InputAction, LogicDigitalData> captureBuffer;
    sdli::util::IndexMap<InputAction, sdli::data::ActionState> currentState; 

protected:


    void handleKeyboard(const Context& ctx, const RawInputData& raw);
    void handleGamecontroller(const Context& ctx, const RawInputData& raw);

    friend class sdli::Device;

public:
    Interface();

    void poll(sdli::Context& ctx);
    void pollAxes(sdli::Context& ctx);

    void push(InputType type, unsigned int rawInput, int value);
    void dispatch(Context& ctx);

    float getRange(InputAxis axis);
    bool isPressed(InputAction action);
    bool isReleased(InputAction action);
    bool isDown(InputAction action);
    bool isUp(InputAction action);

    void swap();
};

} // sdli

#endif // INPUTDEVICE_H
