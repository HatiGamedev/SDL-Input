#ifndef INPUTTESTORACLE_H
#define INPUTTESTORACLE_H

union SDL_Event;

class InputTestOracle
{
public:
    InputTestOracle();

    void generateEvent(SDL_Event* sdl_event);
};

#endif // INPUTTESTORACLE_H
