#include "interface.h"
#include "context.h"
#include <iostream>
#include <SDL2/SDL_events.h>

#include "data/sdli_axis.h"

namespace sdli {


void Interface::handleGamecontroller(const sdli::Context& ctx, const sdli::RawInputData& raw)
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
    : logicAnalogData(12), ///TODO: replace by inputaction count of processor
      captureBuffer(10),
      currentState(10)
{
}

void Interface::poll(sdli::Context& ctx)
{
    auto& axisMap = ctx.axisMapping();

    auto axisIt = axisMap.begin();
    auto axisEnd = axisMap.end();

    for(;axisIt!=axisEnd;++axisIt)
    {
        if(axisIt->idx.deviceType == SDL_Axis::Type::Gamecontroller)
        {
            auto pollResult = 0.0f;
            auto data = axisIt->data;

            if(axisIt->idx.inputType == SDL_Axis::InputType::Digital)
            {
                auto neg = SDL_GameControllerGetButton(this->sdl_gameController, static_cast<SDL_GameControllerButton>(axisIt->idx.axis.rawNegative));
                auto pos = SDL_GameControllerGetButton(this->sdl_gameController, static_cast<SDL_GameControllerButton>(axisIt->idx.axis.rawPositive));

                if(neg == SDL_PRESSED)
                {
                    pollResult -= 1.0f;
                }
                if(pos == SDL_PRESSED)
                {
                    pollResult += 1.0f;
                }
                if(logicAnalogData.at(data->axis)==nullptr)
                {
                    logicAnalogData.emplace(data->axis);
                }
            }
            else
            {
                auto val = SDL_GameControllerGetAxis(this->sdl_gameController,
                                                 static_cast<SDL_GameControllerAxis>(axisIt->idx.rawControllerAxis));

                pollResult = val / 32767.0f;
            }

            auto& currentStatus = logicAnalogData.get(data->axis).currentStatus;
            if(currentStatus!=0.0f)
            {
                currentStatus = sdli::clamp(currentStatus + pollResult, -1, 1) / data->normalize;
            }
            else
            {
                currentStatus = pollResult / data->normalize;
            }

        }
    }
}

void Interface::push(InputType type, unsigned int rawInput, int value)
{
    ///TODO: buffer resize properly
    perFrameCaptures.emplace_back(RawInputData{rawInput, value});
}

//TODO: evaluate isPressed correctly - detect changes over multiple samples
void Interface::dispatch(sdli::Context& ctx)
{
    for(auto& d : perFrameCaptures)
    {
        handleGamecontroller(ctx, d);
    }

    perFrameCaptures.clear();
}

float Interface::getRange(InputAxis axis)
{
    if(logicAnalogData.at(axis) == nullptr)
    {
        return ::sdli::RANGE_UNDEFINED;
    }

    return logicAnalogData.get(axis).currentStatus;
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

    auto pollIt = logicAnalogData.dataBegin();
    auto pollEnd= logicAnalogData.dataEnd();

    for(;pollIt!=pollEnd;++pollIt)
    {
        pollIt->currentStatus = 0.0f;
    }
}

}
