#include "inputdevice.h"
#include "inputcontext.h"
namespace {
    const bool IS_DOWN_UNDEFINED = false;
    const bool IS_UP_UNDEFINED = true;
    const bool IS_RELEASED_UNDEFINED = false;
    const bool IS_PRESSED_UNDEFINED = false;
    const float RANGE_UNDEFINED = 0.0f;
}
namespace sdli {

bool isPressed(const LogicDigitalData& d)
{
    return d.currentStatus
            && d.previousStatus != d.currentStatus;
}

void InputDevice::handleKeyboard(const InputDevice::RawInputData& raw)
{

    auto& ctx = this->contextStack_.top();

    auto inputAction = ctx->keyAction(static_cast<SDL_Scancode>(raw.rawInput));
    auto& logic = logicDigitalData[inputAction];

    logic.previousStatus = logic.currentStatus;
    logic.currentStatus = raw.pollResult;

    if(::sdli::isPressed(logic))
    {
        ctx->fireCallbacks(inputAction, sdli::CallType::OnPress);
    }
}

InputDevice::InputDevice()
{
}

void InputDevice::poll()
{
    if(this->contextStack_.empty())
    {
        return;
    }


    auto sdl_keystate = SDL_GetKeyboardState(NULL);
//    for(auto& i : keyboardKeys)
//    {
//        auto state = sdl_keystate[i.first];
//        logicDigitalData[i.second].previousStatus = logicDigitalData[i.second].currentStatus;
//        logicDigitalData[i.second].currentStatus = state;
//    }


}

void InputDevice::push(InputType type, unsigned int rawInput, int value)
{
    perFrameCaptures.emplace_back(RawInputData{type, rawInput, value});
}

//TODO: evaluate isPressed correctly - detect changes over multiple samples
void InputDevice::dispatch()
{
    if(this->contextStack_.empty())
    {
        return;
    }

    for(auto& i : logicDigitalData)
    {
        i.second.previousStatus = i.second.currentStatus;
        i.second.currentStatus = false;
    }

    for(auto& d : perFrameCaptures)
    {
        switch(d.type)
        {
        case InputType::Keyboard:
            handleKeyboard(d);
            break;
//        case InputType::Keyboard:
//            logicDigitalData[keyboardKeys[static_cast<SDL_Scancode>(d.rawInput)]].currentStatus |= d.pollResult;
//            break;

//        case InputType::GamecontrollerButton:
//            logicDigitalData[gameControllerButtons[static_cast<SDL_GameControllerButton>(d.rawInput)]].currentStatus |= d.pollResult;
//            break;

//        case InputType::GamecontrollerAxis:
//            logicAnalogData[gameControllerAxes[static_cast<SDL_GameControllerAxis>(d.rawInput)].axis].currentStatus = static_cast<float>(d.pollResult);
//            // / gameControllerAxes[static_cast<SDL_GameControllerAxis>(d.rawInput)].normalizeValue;
//            break;
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
    if(contextStack_.empty()
            || logicAnalogData.find(axis) == logicAnalogData.end())
    {
        return RANGE_UNDEFINED;
    }

    return logicAnalogData[axis].currentStatus;
}

bool InputDevice::isPressed(InputAction action)
{
    if(contextStack_.empty()
            || logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::IS_PRESSED_UNDEFINED;
    }

    return logicDigitalData[action].currentStatus
            && logicDigitalData[action].previousStatus != logicDigitalData[action].currentStatus;
}

bool InputDevice::isReleased(InputAction action)
{
    if(contextStack_.empty() || logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::IS_RELEASED_UNDEFINED;
    }

    return !logicDigitalData[action].currentStatus
            && logicDigitalData[action].previousStatus != logicDigitalData[action].currentStatus;;
}

bool InputDevice::isDown(InputAction action)
{
    if(contextStack_.empty() || logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::IS_DOWN_UNDEFINED;
    }
    std::function<void()> test;
    return logicDigitalData[action].currentStatus;
}

bool InputDevice::isUp(InputAction action)
{
    if(contextStack_.empty() || logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::IS_UP_UNDEFINED;
    }

    return logicDigitalData[action].currentStatus;
}

void InputDevice::pushContext(InputContext* newContext)
{
    contextStack_.push(newContext);
}

}
