#ifndef INPUTCONTEXT_H
#define INPUTCONTEXT_H


#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_mouse.h>
#include <map> //TODO: remove


#include "data/sdli_axis.h"

#include "sdli_definitions.h"
#include "util/array.h"
#include "util/indexmap.h"

namespace sdli {

struct InputAxisMapping
{
    InputAxis axis{-1u};
    float normalizeValue{1.0f};
};

struct AxisMapping
{
    sdli::InputAxis axis;
    float normalize{1.0f};

    AxisMapping(sdli::InputAxis axis, float normalize=1.0f)
        : axis(axis),
          normalize(normalize)
    { assert(normalize!=0.0f); }
};

class Context
{


    const sdli::ContextId contextId_;

    sdli::util::IndexMap<SDL_Scancode, InputAction> keyboardKeys_;

    sdli::util::IndexMap<SDL_GameControllerButton, InputAction> gameControllerButtons;

    sdli::util::IndexMap<SDL_Axis, AxisMapping> axisMapping;

    std::map<sdli::InputAction, std::map<sdli::CallType, sdli::CallList>> callbacks;

public:
    Context(const sdli::ContextId& contextId);
    ~Context() {}

    // Uncopyable
    Context(const Context&) =delete;
    Context(Context&&) =delete;
    Context& operator=(const Context&) =delete;
    Context& operator=(Context&&) =delete;

    sdli::ContextId id() const;

    void mapAxis(SDL_GameControllerAxis raw, sdli::InputAxis axis, float normalize=1.0f);
    void mapAxis(SDL_Scancode rawNegative, SDL_Scancode rawPositive, sdli::InputAxis axis);

    // TODO: Mousewheel missing, mouse axes missing

    void mapButton(SDL_Scancode rawKey, sdli::InputAction action);
    void mapButton(SDL_GameControllerButton rawButton, sdli::InputAction action);
    void mapButton(unsigned int rawMouseBtn, sdli::InputAction action);

    void addCallback(sdli::CallType eventType, sdli::InputAction action, const sdli::Callback& callback);

    InputAction keyAction(SDL_Scancode raw) const;
    InputAction keyAction(SDL_GameControllerButton raw) const;


    void fireCallbacks(sdli::InputAction action, sdli::CallType callType) const;

    const sdli::util::IndexMap<SDL_Scancode, InputAction>& keyboardKeys() const;

};


} // sdli



#endif // INPUTCONTEXT_H
