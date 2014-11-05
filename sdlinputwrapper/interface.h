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

#include "util/array.h"

namespace sdli {

class Interface
{
private:
    struct RawInputData
    {
        InputType type;
        unsigned int rawInput;
        int pollResult;
    };

    std::vector<RawInputData> perFrameCaptures;

    std::map<InputAction, LogicDigitalData> logicDigitalData;
    std::map<InputAxis, LogicAnalogData> logicAnalogData;

protected:


    void handleKeyboard(const Context& ctx, const RawInputData& raw);
    void handleGamecontroller(const Context& ctx, const RawInputData& raw);

    friend class sdli::Device;

public:
    Interface();

    void poll(sdli::Context& ctx);
    void push(InputType type, unsigned int rawInput, int value);
    void dispatch(Context& ctx);

    float getRange(InputAxis axis);
    bool isPressed(InputAction action);
    bool isReleased(InputAction action);
    bool isDown(InputAction action);
    bool isUp(InputAction action);

};

} // sdli

#endif // INPUTDEVICE_H
