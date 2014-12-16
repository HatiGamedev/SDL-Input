#include "mouseinterface.h"

#include <SDL_mouse.h>
#include <SDL_events.h>

#include "context.h"



namespace sdli {

MouseInterface::MouseInterface(const int max_actions)
    : logicAnalogData(3),
      captureBuffer(max_actions)
{

}

MouseInterface::~MouseInterface()
{

}

void MouseInterface::poll(Context& ctx)
{
    int posx;
    int posy;

    Uint32 mousebuttonState = SDL_GetMouseState(&posx, &posy);


}

void MouseInterface::push(unsigned int rawInput, int value)
{
    perFrameCaptures.emplace_back(RawInputData{rawInput, value});
}

void MouseInterface::dispatch(Context& ctx)
{
}

float MouseInterface::getRange(InputAxis axis)
{
    if(logicAnalogData.at(axis) == nullptr)
    {
        return ::sdli::RANGE_UNDEFINED;
    }

    return logicAnalogData.get(axis).currentStatus;
}

bool MouseInterface::isPressed(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_PRESSED_UNDEFINED;
    }

    return ::sdli::isPressed(captureBuffer.get(action));
}

bool MouseInterface::isReleased(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_RELEASED_UNDEFINED;
    }

    return ::sdli::isReleased(captureBuffer.get(action));
}

bool MouseInterface::isDown(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_DOWN_UNDEFINED;
    }

    return ::sdli::isDown(captureBuffer.get(action));
}

bool MouseInterface::isUp(InputAction action)
{
    if(captureBuffer.at(action) == nullptr)
    {
        return ::sdli::IS_UP_UNDEFINED;
    }

    return ::sdli::isUp(captureBuffer.get(action));
}

void MouseInterface::swap()
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
