#ifndef ORACLE_INPUTDEVICE_H
#define ORACLE_INPUTDEVICE_H

#include "../context.h"
#include "../util/indexmap.h"
union SDL_Event;

class InputTestOracle
{

public:
    InputTestOracle();

    void generateKeyboardEvent(SDL_Event* sdl_event);
    void testInputEvent(sdli::Context& context);
};

#endif // ORACLE_INPUTDEVICE_H
