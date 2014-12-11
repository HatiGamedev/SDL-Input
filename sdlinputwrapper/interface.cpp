#include "interface.h"
#include "context.h"
#include <iostream>
#include <SDL2/SDL_events.h>

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
    auto inputAction = ctx.keyAction(static_cast<SDL_Scancode>(raw.rawInput));
    if(captureBuffer.at(inputAction) == nullptr)
    {
        captureBuffer.emplace(inputAction);
    }
    auto& logic = captureBuffer.get(inputAction);

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

void Interface::handleGamecontroller(const sdli::Context& ctx, const Interface::RawInputData& raw)
{
    auto inputAction = ctx.keyAction(static_cast<SDL_GameControllerButton>(raw.rawInput));
    if(captureBuffer.at(inputAction) == nullptr)
    {
        captureBuffer.emplace(inputAction);
    }

    auto& logic = captureBuffer.get(inputAction);

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
    : captureBuffer(10), ///TODO: replace by inputaction count of processor
      currentState(10)
{
}

void Interface::poll(sdli::Context& ctx)
{
    auto sdl_keystate = SDL_GetKeyboardState(NULL);

    auto& keymap = ctx.keyboardKeys();
    auto& axisMap = ctx.axisMapping();

    auto axisIt = axisMap.begin();
    auto axisEnd = axisMap.end();

    for(;axisIt!=axisEnd;++axisIt)
    {
        if(axisIt->idx.type == SDL_Axis::Type::Keyboard)
        {
            auto pollResult = 0.0f;

            auto neg = sdl_keystate[axisIt->idx.axis.rawNegative];
            auto pos = sdl_keystate[axisIt->idx.axis.rawPositive];

            if(neg == SDL_PRESSED)
            {
                pollResult -= 1.0f;
            }
            if(pos == SDL_PRESSED)
            {
                pollResult += 1.0f;
            }

            auto data = axisIt->data;
            logicAnalogData[data->axis].currentStatus = pollResult / data->normalize;

        }
    }

    auto it = keymap.begin();
    for(;it!=keymap.end();++it)
    {
        auto state = sdl_keystate[it->idx];
//        auto& data = logicDigitalData[*(it->data)];
//        data.previousStatus = data.currentStatus;
//        data.currentStatus = state;
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
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_PRESSED_UNDEFINED;
    }

    return ::sdli::isPressed(captureBuffer.get(action));
}

bool Interface::isReleased(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_RELEASED_UNDEFINED;
    }

    return ::sdli::isReleased(captureBuffer.get(action));
}

bool Interface::isDown(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_DOWN_UNDEFINED;
    }

    return ::sdli::isDown(captureBuffer.get(action));
}

bool Interface::isUp(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_UP_UNDEFINED;
    }

    return ::sdli::isUp(captureBuffer.get(action));
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
