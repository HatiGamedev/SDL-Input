#ifndef INPUTCONTEXT_H
#define INPUTCONTEXT_H


#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <map>

#include "sdli_definitions.h"
#include "util/array.h"

namespace sdli {

struct InputAxisMapping
{
    InputAxis axis{-1u};
    float normalizeValue{1.0f};
};

class Context
{
    const sdli::ContextId contextId_;

    std::map<SDL_Scancode, InputAction> keyboardKeys_;


    std::map<SDL_GameControllerButton, InputAction> gameControllerButtons;

    sdli::util::Array<InputAxisMapping> gameControllerAxes;
//    std::map<SDL_GameControllerAxis, InputAxisMapping> gameControllerAxes;

    std::map<sdli::InputAction, std::map<sdli::CallType, sdli::CallList>> callbacks_;

public:
    Context(const sdli::ContextId& contextId);
    ~Context() {}

    // Uncopyable
    Context(const Context&) =delete;
    Context(Context&&) =delete;
    Context& operator=(const Context&) =delete;
    Context& operator=(Context&&) =delete;

    sdli::ContextId id() const;

    void mapDigital(SDL_Scancode rawScancode, sdli::InputAction keyAction);
    void mapDigital(SDL_GameControllerButton rawButton, sdli::InputAction keyAction);

    void mapAnalog(SDL_GameControllerAxis rawAxis, sdli::InputAxis axis, float normalize = 1.0f);


    // void mapAxis(SDL_Scancode rawScancode, sdli::InputAxis axis, float normalize=1.0f);

    void addCallback(sdli::InputAction action, sdli::CallType type, const sdli::Callback& callback);
    void fireCallbacks(sdli::InputAction action, sdli::CallType type) const;

    InputAction keyAction(SDL_Scancode rawScancode) const;
    InputAction buttonAction(SDL_GameControllerButton rawButton) const;
    InputAxis controllerAxis(SDL_GameControllerAxis rawAxis) const;

    const std::map<SDL_Scancode, InputAction>& keyboardKeys() const;
    std::map<SDL_Scancode, InputAction>& keyboardKeys();
};

} // sdli

#endif // INPUTCONTEXT_H
