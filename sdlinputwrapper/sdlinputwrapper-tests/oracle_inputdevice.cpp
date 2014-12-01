#include "oracle_inputdevice.h"
#include <SDL2/SDL_events.h>
#include <random>

InputTestOracle::InputTestOracle()
{
    srand(0);
}

void InputTestOracle::generateKeyboardEvent(SDL_Event* sdl_event)
{
    sdl_event->key.keysym.scancode = static_cast<SDL_Scancode>(rand() % SDL_Scancode::SDL_NUM_SCANCODES);
    sdl_event->key.state = rand() % 2;
}

void InputTestOracle::testInputEvent(sdli::Context& context)
{
}


