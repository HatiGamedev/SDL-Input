#include "inputcontext.h"

namespace sdli
{

InputContext::InputContext(const ContextId& contextId)
    : contextId_(contextId)
{
}

ContextId InputContext::id() const
{
    return this->contextId_;
}



void InputContext::mapDigital(SDL_Scancode raw, InputAction a)
{
    keyboardKeys.emplace(std::make_pair(raw, a));
}

void InputContext::mapDigital(SDL_GameControllerButton raw, InputAction a)
{
    gameControllerButtons.emplace(std::make_pair(raw, a));
}

void InputContext::mapAnalog(SDL_GameControllerAxis raw, InputAxis a, float normalize)
{
    gameControllerAxes.emplace(std::make_pair(raw, InputAxisMapping{a, normalize}));
}

void InputContext::addCallback(InputAction action, CallType type, const Callback& callback)
{
    auto& actionMap = callbacks_[action];
    auto& typeCallbacks = actionMap[type];

    typeCallbacks.emplace_back(callback);
}

void InputContext::fireCallbacks(InputAction action, CallType type)
{
    auto& callbacks = callbacks_[action][type];
    for(auto& c : callbacks)
    {
        c();
    }
}

InputAction InputContext::keyAction(SDL_Scancode rawScancode) const
{
    if(keyboardKeys.find(rawScancode) == keyboardKeys.end())
    {
        return sdli::INVALID_INPUT_ACTION;
    }

    return keyboardKeys.at(rawScancode);
}

InputAction InputContext::buttonAction(SDL_GameControllerButton rawButton) const
{
    if(gameControllerButtons.find(rawButton) == gameControllerButtons.end())
    {
        return sdli::INVALID_INPUT_ACTION;
    }

    return gameControllerButtons.at(rawButton);
}

InputAxis InputContext::controllerAxis(SDL_GameControllerAxis rawAxis) const
{
    if(gameControllerAxes.find(rawAxis) == gameControllerAxes.end())
    {
        return sdli::INVALID_INPUT_AXIS;
    }

    return gameControllerAxes.at(rawAxis).axis;
}










} // sdli
