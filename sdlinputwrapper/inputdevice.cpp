#include "inputdevice.h"

namespace sdli {

namespace {
    const bool IS_RELEASED_UNDEFINED = true;
    const bool IS_PRESSED_UNDEFINED = false;
}

InputDevice::InputDevice()
{
}

void InputDevice::push(InputType type, int rawInput, int value)
{
    perFrameCaptures.emplace_back(RawInputData{type, rawInput, value});
}

void InputDevice::dispatch()
{
    for(auto& d : perFrameCaptures)
    {
        switch(d.type)
        {
        case InputType::Keyboard:
            logicDigitalData[keyboardKeys[static_cast<SDL_Scancode>(d.rawInput)]].currentStatus = d.pollResult;
            break;

        case InputType::GamecontrollerButton:
            logicDigitalData[gameControllerButtons[static_cast<SDL_GameControllerButton>(d.rawInput)]].currentStatus = d.pollResult;
            break;

        case InputType::GamecontrollerAxis:
            logicAnalogData[gameControllerAxes[static_cast<SDL_GameControllerAxis>(d.rawInput)].axis].currentStatus = static_cast<float>(d.pollResult);
            // / gameControllerAxes[static_cast<SDL_GameControllerAxis>(d.rawInput)].normalizeValue;
            break;
//        case InputType::MouseButton:
//            // TBA - Req for public ?
//            break;
//        case InputType::MouseAxis:
//            // TBA - Req for public ?
//            break;
        }
    }

    perFrameCaptures.clear();
}

float InputDevice::getRange(InputAxis axis)
{
    if(logicAnalogData.find(axis) == logicAnalogData.end())
        return 0.0f;

    return logicAnalogData[axis].currentStatus;
}

bool InputDevice::isPressed(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return IS_PRESSED_UNDEFINED;
    }

    return logicDigitalData[action].currentStatus == 1
            && logicDigitalData[action].previousStatus != logicDigitalData[action].currentStatus;
}

bool InputDevice::isReleased(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return IS_RELEASED_UNDEFINED;
    }

    return logicDigitalData[action].currentStatus == 0
            && logicDigitalData[action].previousStatus != logicDigitalData[action].currentStatus;;
}

bool InputDevice::isDown(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return IS_PRESSED_UNDEFINED;
    }

    return logicDigitalData[action].currentStatus == 1;
}

bool InputDevice::isUp(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return IS_RELEASED_UNDEFINED;
    }

    return logicDigitalData[action].currentStatus == 0;
}

void InputDevice::map(SDL_Scancode raw, InputAction a)
{
    keyboardKeys.emplace(std::make_pair(raw, a));
}

void InputDevice::map(SDL_GameControllerButton raw, InputAction a)
{
    gameControllerButtons.emplace(std::make_pair(raw, a));
}

void InputDevice::map(SDL_GameControllerAxis raw, InputAxis a, float normalize)
{
    gameControllerAxes.emplace(std::make_pair(raw, InputAxisMapping{a, normalize}));
}

}
