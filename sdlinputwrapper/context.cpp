#include "context.h"

namespace sdli
{

Context::Context(const ContextId& contextId)
    : contextId_(contextId),
      gameControllerAxes(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_MAX)
{
}

ContextId Context::id() const
{
    return this->contextId_;
}



void Context::mapDigital(SDL_Scancode raw, InputAction a)
{
    keyboardKeys_.emplace(std::make_pair(raw, a));
}

void Context::mapDigital(SDL_GameControllerButton raw, InputAction a)
{
    gameControllerButtons.emplace(std::make_pair(raw, a));
}

void Context::mapAxis(SDL_GameControllerAxis raw, InputAxis a, float normalize)
{
    gameControllerAxes[raw] = InputAxisMapping{};
    gameControllerAxes[raw].axis = a;
    gameControllerAxes[raw].normalizeValue = normalize;
    //    gameControllerAxes.emplace(std::make_pair(raw, InputAxisMapping{a, normalize}));
}

void Context::mapAxis(SDL_Scancode rawScancode, InputAxis axis, float normalize)
{

}

void Context::mapAxis(SDL_GameControllerButton, InputAxis axis, float normalize)
{

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
    if(keyboardKeys_.find(rawScancode) == keyboardKeys_.end())
    {
        return sdli::INVALID_INPUT_ACTION;
    }

    return keyboardKeys_.at(rawScancode);
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

    if(gameControllerAxes[rawAxis].axis == -1u)
    {
        return sdli::INVALID_INPUT_AXIS;
    }

    return gameControllerAxes[rawAxis].axis;
}

const std::map<SDL_Scancode, InputAction>& Context::keyboardKeys() const
{
    return keyboardKeys_;
}

std::map<SDL_Scancode, InputAction>&Context::keyboardKeys()
{
    return keyboardKeys_;
}


} // sdli
