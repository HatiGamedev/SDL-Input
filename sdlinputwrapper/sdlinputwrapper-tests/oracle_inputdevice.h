#ifndef ORACLE_INPUTDEVICE_H
#define ORACLE_INPUTDEVICE_H

union SDL_Event;

struct InputDeviceOracleResult
{
    bool isDown;
    bool isUp;
    bool isReleased;
    bool isPressed;
};


class InputTestOracle
{
public:
    InputTestOracle();

    void generateKeyboardEvent(SDL_Event* sdl_event);
};

#endif // ORACLE_INPUTDEVICE_H
