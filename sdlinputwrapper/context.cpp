#include "context.h"

namespace sdli
{

Context::Context(const ContextId& contextId)
    : contextId_(contextId),
      keyboardKeys_(128), ///TODO: make variable
      //gameControllerAxes(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX)
      axisMapping(12) ///TODO: make
{
}

ContextId Context::id() const
{
    return this->contextId_;
}

void Context::mapAxis(SDL_GameControllerAxis raw, InputAxis axis, float normalize)
{
    STUB();
    assert(raw != SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID);
}

void Context::mapAxis(SDL_Scancode rawNegative, SDL_Scancode rawPositive, sdli::InputAxis axis)
{
    axisMapping.emplace({rawNegative, rawPositive}, axis);
}

void Context::mapButton(SDL_Scancode rawKey, InputAction action)
{
    keyboardKeys_.emplace(rawKey, action);
}

void Context::mapButton(SDL_GameControllerButton rawButton, InputAction action)
{
    STUB();
}

void Context::addCallback(CallType eventType, InputAction action, const Callback& callback)
{
    callbacks[action][eventType].emplace_back(callback);
}

InputAction Context::keyAction(SDL_Scancode raw) const
{
    auto action = keyboardKeys_.at(raw);
    if(action == nullptr)
    {
        return sdli::INVALID_INPUT_ACTION;
    }
    return *action;
}

void Context::fireCallbacks(InputAction action, CallType callType) const
{
    auto it = callbacks.find(action);
    if( it != callbacks.end()
            && it->second.find(callType) != it->second.end())
    {
        auto& callbacks_ = callbacks.at(action).at(callType);
        for(auto& c : callbacks_)
        {
            c();
        }
    }
}

const sdli::util::IndexMap<SDL_Scancode, InputAction>& Context::keyboardKeys() const
{
    return keyboardKeys_;
}

} // sdli

