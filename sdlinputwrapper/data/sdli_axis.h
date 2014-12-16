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
    struct DigitalAxis
    {
        unsigned short rawNegative;
        unsigned short rawPositive;
    };

    union
    {
        DigitalAxis axis;
        unsigned int rawControllerAxis;
        unsigned int rawMouseAxis;
    };

    enum class Type
    {
        Keyboard,
        Gamecontroller,
        Mouse
    } deviceType;

    enum class InputType
    {
        Digital,
        Analog
    } inputType;

    SDL_Axis()
        : rawControllerAxis(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_INVALID),
          deviceType(Type::Gamecontroller),
          inputType(InputType::Analog) {}

    SDL_Axis(SDL_GameControllerAxis raw)
        : rawControllerAxis(raw),
          deviceType(Type::Gamecontroller),
          inputType(InputType::Analog) {}

    SDL_Axis(SDL_GameControllerButton negative, SDL_GameControllerButton positive)
        : deviceType(Type::Gamecontroller),
          inputType(InputType::Digital)
    {
        axis.rawNegative = negative;
        axis.rawPositive = positive;
    }

    SDL_Axis(SDL_Scancode negative, SDL_Scancode positive)
        : deviceType(Type::Keyboard),
          inputType(InputType::Digital)
    {
        axis.rawNegative = negative;
        axis.rawPositive = positive;
    }

    SDL_Axis(SDLI_MouseAxis raw)
        :rawMouseAxis(static_cast<int>(raw)),
         deviceType(Type::Mouse),
         inputType(InputType::Analog) {}
};
} // sdli
bool operator==(const sdli::SDL_Axis& a1, const sdli::SDL_Axis& a2);

#endif // SDLI_AXIS_H
