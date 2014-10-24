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

namespace sdli {

class InputDevice
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
    std::stack<sdli::InputContext*> contextStack_;

    void handleKeyboard(const RawInputData& raw);
    void handleGamecontroller(const RawInputData& raw);

public:
    InputDevice();

    void poll();
    void push(InputType type, unsigned int rawInput, int value);
    void dispatch();

    float getRange(InputAxis axis);
    bool isPressed(InputAction action);
    bool isReleased(InputAction action);
    bool isDown(InputAction action);
    bool isUp(InputAction action);

    void pushContext(sdli::InputContext* newContext);
    sdli::InputContext* popContext();

};

} // sdli

#endif // INPUTDEVICE_H
