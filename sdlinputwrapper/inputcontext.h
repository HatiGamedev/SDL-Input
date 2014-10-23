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
    const sdli::ContextId contextId_;

    std::map<InputAction, LogicDigitalData> digitalData;
    std::map<InputAction, LogicAnalogData> anaogData;

public:
    InputContext(const sdli::ContextId& contextId);

    InputContext(const InputContext&) =delete;
    InputContext(InputContext&&) =delete;
    InputContext& operator=(const InputContext&) =delete;
    InputContext& operator=(InputContext&&) =delete;


    void poll();

    sdli::ContextId id() const;

    void mapDigital(SDL_Scancode rawScancode, sdli::InputAction action);
    void mapDigital(SDL_GameControllerButton rawButton, sdli::InputAction action);


    void mapAnalog(SDL_GameControllerAxis rawAxis, sdli::InputAxis axis, float normalize = 1.0f);
};

} // sdli

#endif // INPUTCONTEXT_H
