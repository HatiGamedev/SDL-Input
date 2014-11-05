#include "interface.h"
#include "context.h"

namespace sdli {

bool isPressed(const LogicDigitalData& d)
{
    return d.currentStatus
            && d.previousStatus != d.currentStatus;
}

bool isReleased(const LogicDigitalData& d)
{
    return !d.currentStatus
            && d.previousStatus != d.currentStatus;
}

bool isDown(const LogicDigitalData& d)
{
    return d.currentStatus;
}

bool isUp(const LogicDigitalData& d)
{
    return !d.currentStatus;
}

void Interface::handleKeyboard(const sdli::Context& ctx, const Interface::RawInputData& raw)
{
//    auto& ctx = this->contextStack_.top();

    auto inputAction = ctx.keyAction(static_cast<SDL_Scancode>(raw.rawInput));
    auto& logic = logicDigitalData[inputAction];

//    logic.previousStatus = logic.currentStatus;
    logic.currentStatus = raw.pollResult;

    if(::sdli::isPressed(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnPress);
        return;
    }
    if(::sdli::isReleased(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnRelease);
        return;
    }

}

void Interface::handleGamecontroller(const sdli::Context& ctx, const Interface::RawInputData& raw)
{
//    auto& ctx = this->contextStack_.top();

    auto inputAction = ctx.buttonAction(static_cast<SDL_GameControllerButton>(raw.rawInput));
    auto& logic = logicDigitalData[inputAction];

    logic.currentStatus = raw.pollResult;

    if(::sdli::isPressed(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnPress);
    }

    if(::sdli::isReleased(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnRelease);
    }

}

Interface::Interface()
{
}

void Interface::poll(sdli::Context& ctx)
{
    unsigned int t = SDL_Scancode::SDL_NUM_SCANCODES;

    auto sdl_keystate = SDL_GetKeyboardState(NULL);

    auto& keymap = ctx.keyboardKeys();

    for(auto& k : keymap)
    {
        auto state = sdl_keystate[k.first];
        auto& data = logicDigitalData[k.second];
        data.previousStatus = data.currentStatus;
        data.currentStatus = state;
    }
}

void Interface::push(InputType type, unsigned int rawInput, int value)
{
    perFrameCaptures.emplace_back(RawInputData{type, rawInput, value});
}

//TODO: evaluate isPressed correctly - detect changes over multiple samples
void Interface::dispatch(sdli::Context& ctx)
{
    for(auto& i : logicDigitalData)
    {
        i.second.previousStatus = i.second.currentStatus;
    }

    for(auto& d : perFrameCaptures)
    {
        switch(d.type)
        {
        case InputType::Keyboard:
            handleKeyboard(ctx, d);
            break;

        case InputType::Gamecontroller:
            handleGamecontroller(ctx, d);
            break;
        default:
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

float Interface::getRange(InputAxis axis)
{
    if(logicAnalogData.find(axis) == logicAnalogData.end())
    {
        return ::sdli::RANGE_UNDEFINED;
    }

    return logicAnalogData[axis].currentStatus;
}

bool Interface::isPressed(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::sdli::IS_PRESSED_UNDEFINED;
    }

    auto& l = logicDigitalData[action];

    return ::sdli::isPressed(l);
}

bool Interface::isReleased(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::sdli::IS_RELEASED_UNDEFINED;
    }

    auto& l = logicDigitalData[action];

    return ::sdli::isReleased(l);
}

bool Interface::isDown(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::sdli::IS_DOWN_UNDEFINED;
    }

    auto& l = logicDigitalData[action];

    return ::sdli::isDown(l);
}

bool Interface::isUp(InputAction action)
{
    if(logicDigitalData.find(action) == logicDigitalData.end())
    {
        return ::sdli::IS_UP_UNDEFINED;
    }

    auto& l = logicDigitalData[action];

    return ::sdli::isUp(l);
}

}
