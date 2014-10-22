#ifndef INPUTCONTEXT_H
#define INPUTCONTEXT_H


#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <map>

#include "sdli_definitions.h"

namespace sdli {

class InputContext
{
    struct InputAxisMapping
    {
        InputAxis axis;
        float normalizeValue;
    };


    const sdli::ContextId contextId_;


    std::map<SDL_Scancode, InputAction> keyboardKeys;

    std::map<SDL_GameControllerButton, InputAction> gameControllerButtons;
    std::map<SDL_GameControllerAxis, InputAxisMapping> gameControllerAxes;

    std::map<unsigned int, std::map<sdli::CallType, sdli::CallList>> callbacks_;

public:
    InputContext(const sdli::ContextId& contextId);

    InputContext(const InputContext&) =delete;
    InputContext(InputContext&&) =delete;
    InputContext& operator=(const InputContext&) =delete;
    InputContext& operator=(InputContext&&) =delete;

    sdli::ContextId id() const;

    void mapDigital(SDL_Scancode rawScancode, sdli::InputAction keyAction);
    void mapDigital(SDL_GameControllerButton rawButton, sdli::InputAction keyAction);

    void mapAnalog(SDL_GameControllerAxis rawAxis, sdli::InputAxis axis, float normalize = 1.0f);

    void addCallback(sdli::InputAction action, sdli::CallType type, const sdli::Callback& callback);
    void fireCallbacks(sdli::InputAction action, sdli::CallType type);

    InputAction keyAction(SDL_Scancode rawScancode) const;
    InputAction buttonAction(SDL_GameControllerButton rawButton) const;
    InputAxis controllerAxis(SDL_GameControllerAxis rawAxis) const;
};

} // sdli

#endif // INPUTCONTEXT_H