#include "processor.h"
#include <assert.h>
#include "context.h"
#include "interface.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace sdli
{

Interface*Processor::getControllerInterface(Sint32 controllerId)
{
    auto controller = SDL_GameControllerOpen(controllerId);

    printf("attached: %i\n", SDL_GameControllerGetAttached(controller));
    printf("evenstate: %i\n", SDL_GameControllerEventState(SDL_QUERY));  /* prints 0 */

    unsigned int joystickId = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
    printf("joystick-id: %u\n", joystickId);

    bool isReconnect = false;
    Sint32 prevJoystickId = 0;

    if(hardwareIdToJoystickId.at(controllerId)==nullptr)
    {
        hardwareIdToJoystickId.emplace(controllerId, joystickId);
        printf("link %d:%d\n", controllerId, joystickId);
    }
    else
    {
        prevJoystickId = hardwareIdToJoystickId.get(controllerId);
        hardwareIdToJoystickId.get(controllerId) = joystickId;
        printf("relink %d:%d\n", controllerId, hardwareIdToJoystickId.get(controllerId));
        isReconnect = true;
    }


    if(!isReconnect && gamecontrollerInterfaces.at(hardwareIdToJoystickId.get(controllerId))==nullptr)
    {
        printf("creating new interface ..@%d\n", hardwareIdToJoystickId.get(controllerId));
        gamecontrollerInterfaces.emplace(hardwareIdToJoystickId.get(controllerId), new sdli::Interface);
    }
    else
    {
        gamecontrollerInterfaces.move(prevJoystickId, hardwareIdToJoystickId.get(controllerId));
        printf("Recycle existing device! Move from %d to %d\n", prevJoystickId, hardwareIdToJoystickId.get(controllerId));
    }
    return gamecontrollerInterfaces.get(hardwareIdToJoystickId.get(controllerId)).get();
}

void Processor::addController(Sint32 controllerId)
{
    auto controller = SDL_GameControllerOpen(controllerId);

    printf("attached: %i\n", SDL_GameControllerGetAttached(controller));
    printf("evenstate: %i\n", SDL_GameControllerEventState(SDL_QUERY));  /* prints 0 */

    unsigned int joystickId = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
    printf("joystick-id: %u\n", joystickId);

    bool isReconnect = false;
    Sint32 prevJoystickId = 0;

    if(hardwareIdToJoystickId.at(controllerId)==nullptr)
    {
        hardwareIdToJoystickId.emplace(controllerId, joystickId);
        printf("link %d:%d\n", controllerId, joystickId);
    }
    else
    {
        prevJoystickId = hardwareIdToJoystickId.get(controllerId);
        hardwareIdToJoystickId.get(controllerId) = joystickId;
        printf("relink %d:%d\n", controllerId, hardwareIdToJoystickId.get(controllerId));
        isReconnect = true;
    }


    if(!isReconnect && gamecontrollerInterfaces.at(hardwareIdToJoystickId.get(controllerId))==nullptr)
    {
        printf("creating new interface ..@%d\n", hardwareIdToJoystickId.get(controllerId));
        gamecontrollerInterfaces.emplace(hardwareIdToJoystickId.get(controllerId), new sdli::Interface);
    }
    else
    {
        gamecontrollerInterfaces.move(prevJoystickId, hardwareIdToJoystickId.get(controllerId));
        printf("Recycle existing device! Move from %d to %d\n", prevJoystickId, hardwareIdToJoystickId.get(controllerId));
    }
    getControllerDevice(controllerId);
}

Device& Processor::getControllerDevice(Sint32 hardwareId)
{
    if(gamecontrollerDevices.at(hardwareId) == nullptr) // non existend -> emplace
    {
        printf("Create empty device %d\n", hardwareId );
        gamecontrollerDevices.emplace(hardwareId, new sdli::Device()); // create unlinked device
        devices.push_back(&(*gamecontrollerDevices.get(hardwareId)));
    }
    else
    {
        gamecontrollerInterfaces.get(hardwareIdToJoystickId.get(hardwareId)).get()->sdl_gameController = SDL_GameControllerOpen(hardwareId);
        gamecontrollerDevices.get(hardwareId)->setInterface(gamecontrollerInterfaces.get(hardwareIdToJoystickId.get(hardwareId)).get());

    }

    auto& t = *gamecontrollerDevices.get(hardwareId);

    return t;
}

Processor::Processor(unsigned int maxContexts)
    : contextMap(maxContexts),
      keyboard(new sdli::KeyboardInterface(10, 10)), ///TODO: make max_counts variable
      keyboardDevice(),
      mouse(new sdli::MouseInterface(10)),
      mouseDevice(),
      gamecontrollerInterfaces(10), ///TODO: make dynamic controller count
      hardwareIdToJoystickId(10),
      gamecontrollerDevices(10)
{
    keyboardDevice.setKeyboard(keyboard.get());
    devices.push_back(&keyboardDevice);
}


sdli::Context* Processor::createContext(const sdli::ContextId& contextId)
{
    /* Only one type of context allowed per processor */
//    assert(contextMap.find(contextId) == contextMap.end());
    contextMap.emplace_at(contextId, contextId);

    return &contextMap[contextId];
}

sdli::Context* Processor::getContext(const sdli::ContextId& contextId)
{
    return &contextMap[contextId];
}

Device& Processor::getKeyboard()
{
    return keyboardDevice;
}

Device&Processor::getMouse()
{
    return mouseDevice;
}

Device&Processor::getGamecontroller(unsigned int id)
{
    return getControllerDevice(id);
}

Device&Processor::getDevice(InputType type)
{
    return keyboardDevice;
}

void Processor::handleSdlEvents(const SDL_Event& e)
{
    switch(e.type)
    {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
//        printf("Key-input: %d : %d", e.key.keysym.scancode, e.key.state);
        if(sdlEventFlag & sdli::ProcessorEventFlags::Keyboard)
        {
            keyboard->push(e.key.keysym.scancode, e.key.state);
        }
        break;
    case SDL_CONTROLLERDEVICEADDED:
        if(sdlEventFlag & sdli::ProcessorEventFlags::ControllerConnect)
        {
            printf("Controller added: %u\n", e.cdevice.which); // which := hardware-id
            addController(e.cdevice.which);
        }
        break;
    case SDL_CONTROLLERDEVICEREMOVED:
        if(sdlEventFlag & sdli::ProcessorEventFlags::ControllerConnect)
        {
            printf("Controller removed: %u\n", e.cdevice.which); // which := instance-id
        }
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        if(sdlEventFlag & sdli::ProcessorEventFlags::ControllerButtons)
        {
//            printf("Controller button-down: %u\n", e.cdevice.which); // which := instance-id
            if(gamecontrollerInterfaces.at(e.cbutton.which)!=nullptr)
            {
                gamecontrollerInterfaces.get(e.cbutton.which)->push(InputType::Gamecontroller, e.cbutton.button, e.cbutton.state);
            }
        }
        break;
    case SDL_CONTROLLERBUTTONUP:
        if(sdlEventFlag & sdli::ProcessorEventFlags::ControllerButtons)
        {
            if(gamecontrollerInterfaces.at(e.cbutton.which)!=nullptr)
            {
                gamecontrollerInterfaces.get(e.cbutton.which)->push(InputType::Gamecontroller, e.cbutton.button, e.cbutton.state);
            }
        }
        break;
    }
}

void Processor::dispatch()
{
    for(auto& d : devices)
    {
        d->dispatch();
    }
}

void Processor::poll()
{
    for(auto& d : devices)
    {
        d->poll();
    }
}

void Processor::swap()
{
    for(auto& d : devices)
    {
        d->swap();
    }
}

} // sdli
