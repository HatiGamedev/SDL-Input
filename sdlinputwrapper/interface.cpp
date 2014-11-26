#include "interface.h"
#include "context.h"
#include <iostream>

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
    /*
    auto inputAction = ctx.keyAction(static_cast<SDL_Scancode>(raw.rawInput));
    auto& logic = logicDigitalData[inputAction];

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
    */

    auto inputAction = ctx.keyAction(static_cast<SDL_Scancode>(raw.rawInput));
    if(captureBuffer.at(inputAction) == nullptr)
    {
        captureBuffer.emplace(inputAction);
    }
    auto& logic = captureBuffer.get(inputAction);

    logic.currentStatus = raw.pollResult;
//    sdli::data::push(logic.current, raw.pollResult);

    if(::sdli::isPressed(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnPress);
    }

    if(::sdli::isReleased(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnRelease);
    }

}

void Interface::handleGamecontroller(const sdli::Context& ctx, const Interface::RawInputData& raw)
{
//    auto& ctx = this->contextStack_.top();

    STUB(auto inputAction = ctx.buttonAction(static_cast<SDL_GameControllerButton>(raw.rawInput));
    auto& logic = logicDigitalData[inputAction];

    logic.currentStatus = raw.pollResult;

    if(::sdli::isPressed(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnPress);
    }

    if(::sdli::isReleased(logic))
    {
        ctx.fireCallbacks(inputAction, sdli::CallType::OnRelease);
    });

}

Interface::Interface()
    : captureBuffer(10) ///TODO: replace by inputaction count of processor
{
}

void Interface::poll(sdli::Context& ctx)
{
    auto sdl_keystate = SDL_GetKeyboardState(NULL);

    auto& keymap = ctx.keyboardKeys();

    auto it = keymap.begin();
    for(;it!=keymap.end();++it)
    {
        auto state = sdl_keystate[it->idx];
        auto& data = logicDigitalData[*(it->data)];
        data.previousStatus = data.currentStatus;
        data.currentStatus = state;
    }
}

void Interface::pollAxes(Context& ctx)
{

}

void Interface::push(InputType type, unsigned int rawInput, int value)
{
    ///TODO: buffer resize properly
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
            STUB(handleGamecontroller(ctx, d););
            break;
        default:
            break;
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

void Interface::swap()
{
    auto it = captureBuffer.dataBegin();
    auto end = captureBuffer.dataEnd();
    for(;it!=end;++it)
    {
        it->previousStatus = it->currentStatus;
    }
}

}
