#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "inputaction.h"
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <map>
#include <vector>


namespace sdli {

struct LogicDigitalData
{
    bool currentStatus{false};
    bool previousStatus{false};
};

struct LogicAnalogData
{
    float currentStatus{0.0f};
};

enum class InputType
{
    Keyboard,
//    MouseAxis,
//    MouseButton,
    GamecontrollerButton,
    GamecontrollerAxis
};

class InputDevice
{
private:
    struct RawInputData
    {
        InputType type;
        int rawInput;
        int pollResult;
    };

    std::vector<RawInputData> perFrameCaptures;

    std::map<InputAction, LogicDigitalData> logicDigitalData;
    std::map<InputAxis, LogicAnalogData> logicAnalogData;
protected:


    struct InputAxisMapping
    {
        InputAxis axis;
        float normalizeValue;
    };

    std::map<SDL_Scancode, InputAction> keyboardKeys;

    std::map<SDL_GameControllerButton, InputAction> gameControllerButtons;
    std::map<SDL_GameControllerAxis, InputAxisMapping> gameControllerAxes;

public:
    InputDevice();


    void push(InputType type, int rawInput, int value);
    void dispatch();

    float getRange(InputAxis axis);
    bool isPressed(InputAction action);
    bool isReleased(InputAction action);

    void map(SDL_Scancode raw, InputAction a);
    void map(SDL_GameControllerButton raw, InputAction a);
    void map(SDL_GameControllerAxis raw, InputAxis a, float normalize);
};
} // sdli

#endif // INPUTDEVICE_H
