#ifndef SDLI_AXIS_H
#define SDLI_AXIS_H

#include <SDL2/SDL_gamecontroller.h>
#include <SDL2/SDL_keyboard.h>

namespace sdli {

enum class SDLI_MouseAxis
{
    Horizontal,
    Vertical
};

struct SDL_Axis
{
    struct KeyboardAxis
    {
        unsigned short rawNegative;
        unsigned short rawPositive;
    };

    union
    {
        KeyboardAxis axis;
        unsigned int rawControllerAxis;
        unsigned int rawMouseAxis;
    };

    enum class Type
    {
        Keyboard,
        GameController,
        Mouse
    } type;

    SDL_Axis()
        : rawControllerAxis(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID),
          type(Type::GameController) {}

    SDL_Axis(SDL_GameControllerAxis raw)
        : rawControllerAxis(raw),
          type(Type::GameController) {}

    SDL_Axis(SDL_Scancode negative, SDL_Scancode positive)
        : type(Type::Keyboard)
    {
        axis.rawNegative = negative;
        axis.rawPositive = positive;
    }

    SDL_Axis(SDLI_MouseAxis raw)
        :rawMouseAxis(raw),
         type(Type::Mouse)
    {
    }
};
} // sdli
bool operator==(const sdli::SDL_Axis& a1, const sdli::SDL_Axis& a2);

#endif // SDLI_AXIS_H
