#include "keyboardinterface.h"

#include <SDL_keyboard.h>
#include <SDL_events.h>

#include "context.h"



namespace sdli {

KeyboardInterface::KeyboardInterface(const int max_actions, const int max_axes)
    : logicAnalogData(max_axes),
      captureBuffer(max_actions)
{

}

KeyboardInterface::~KeyboardInterface()
{

}

void KeyboardInterface::poll(Context& ctx)
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
            auto data = axisIt->data;

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
            if(logicAnalogData.at(data->axis)==nullptr)
            {
                logicAnalogData.emplace(data->axis);
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

    auto it = keymap.begin();



    for(;it!=keymap.end();++it)
    {
        auto state = sdl_keystate[it->idx];
        auto action = *(it->data);
        if(captureBuffer.at(action)==nullptr)
        {
            captureBuffer.emplace(action);
        }

        captureBuffer.get(action).previousStatus = captureBuffer.get(action).currentStatus;
        captureBuffer.get(action).currentStatus = state;
    }
}

void KeyboardInterface::push(unsigned int rawInput, int value)
{
    perFrameCaptures.emplace_back(RawInputData{rawInput, value});
}

void KeyboardInterface::dispatch(Context& ctx)
{
    for(auto& raw : perFrameCaptures)
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
}

float KeyboardInterface::getRange(InputAxis axis)
{
    if(logicAnalogData.at(axis) == nullptr)
    {
        return ::sdli::RANGE_UNDEFINED;
    }

    return logicAnalogData.get(axis).currentStatus;
}

bool KeyboardInterface::isPressed(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_PRESSED_UNDEFINED;
    }

    return ::sdli::isPressed(captureBuffer.get(action));
}

bool KeyboardInterface::isReleased(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_RELEASED_UNDEFINED;
    }

    return ::sdli::isReleased(captureBuffer.get(action));
}

bool KeyboardInterface::isDown(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_DOWN_UNDEFINED;
    }

    return ::sdli::isDown(captureBuffer.get(action));
}

bool KeyboardInterface::isUp(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_UP_UNDEFINED;
    }

    return ::sdli::isUp(captureBuffer.get(action));
}

void KeyboardInterface::swap()
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




} // sdli
