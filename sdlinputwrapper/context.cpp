#include "context.h"

namespace sdli
{

Context::Context(const ContextId& contextId)
    : contextId_(contextId)
{
}

ContextId Context::id() const
{
    return this->contextId_;
}



void Context::mapDigital(SDL_Scancode raw, InputAction a)
{
    keyboardKeys.emplace(std::make_pair(raw, a));
}

void Context::mapDigital(SDL_GameControllerButton raw, InputAction a)
{
    gameControllerButtons.emplace(std::make_pair(raw, a));
}

void Context::mapAnalog(SDL_GameControllerAxis raw, InputAxis a, float normalize)
{
    gameControllerAxes.emplace(std::make_pair(raw, InputAxisMapping{a, normalize}));
}

void Context::addCallback(InputAction action, CallType type, const Callback& callback)
{
    auto& actionMap = callbacks_[action];
    auto& typeCallbacks = actionMap[type];

    typeCallbacks.emplace_back(callback);
}

void Context::fireCallbacks(InputAction action, CallType type) const
{
    auto it = callbacks_.find(action);
    if( it != callbacks_.end()
            && it->second.find(type) != it->second.end())
    {
        auto& callbacks = callbacks_.at(action).at(type);
        for(auto& c : callbacks)
        {
            c();
        }
    }
}

InputAction Context::keyAction(SDL_Scancode rawScancode) const
{
    if(keyboardKeys.find(rawScancode) == keyboardKeys.end())
    {
        return sdli::INVALID_INPUT_ACTION;
    }

    return keyboardKeys.at(rawScancode);
}

InputAction Context::buttonAction(SDL_GameControllerButton rawButton) const
{
    if(gameControllerButtons.find(rawButton) == gameControllerButtons.end())
    {
        return sdli::INVALID_INPUT_ACTION;
    }

    return gameControllerButtons.at(rawButton);
}

InputAxis Context::controllerAxis(SDL_GameControllerAxis rawAxis) const
{
    if(gameControllerAxes.find(rawAxis) == gameControllerAxes.end())
    {
        return sdli::INVALID_INPUT_AXIS;
    }

    return gameControllerAxes.at(rawAxis).axis;
}


} // sdli
