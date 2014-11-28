#include "processor.h"
#include <assert.h>
#include "context.h"
#include "interface.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace sdli
{

void Processor::addController(Sint32 controllerId)
{
    auto controller = SDL_GameControllerOpen(controllerId);

    printf("attached: %i\n", SDL_GameControllerGetAttached(controller));
    printf("evenstate: %i\n", SDL_GameControllerEventState(SDL_QUERY));  /* prints 0 */

    unsigned int joystickId = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
    printf("joystick-id: %u\n", joystickId);
    if(hardwareToJoystickId.at(controllerId)==nullptr)
    {
        hardwareToJoystickId.emplace(controllerId, joystickId);
        printf("link %d:%d\n", controllerId, joystickId);
    }
    else
    {
        hardwareToJoystickId.get(controllerId) = joystickId;
        printf("relink %d:%d\n", controllerId, joystickId);
    }

    if(gamecontrollers.at(joystickId)==nullptr)
    {
        std::cout << "creating new interface .." << std::endl;
        gamecontrollers.emplace(joystickId, new sdli::Interface);
    }
    else
    {
        std::cout << "recycle old interface" <<std::endl;
    }
    getControllerDevice(controllerId);

}

Device& Processor::getControllerDevice(Sint32 hardwareId)
{
    if(gamecontrollerDevices.at(hardwareId) == nullptr) // non existend -> emplace
    {
        gamecontrollerDevices.emplace(hardwareId, new sdli::Device(nullptr)); // create unlinked device
        devices.push_back(&(*gamecontrollerDevices.get(hardwareId)));
    }
    else
    {
        gamecontrollerDevices.get(hardwareId)->setInterface(gamecontrollers.get(hardwareToJoystickId.get(hardwareId)).get());

    }

    auto& t = *gamecontrollerDevices.get(hardwareId);

    return t;
}

Processor::Processor(unsigned int maxContexts)
    : contextMap(maxContexts),
      keyboard(new sdli::Interface),
      gamecontrollers(10), ///TODO: make dynamic controller count
      hardwareToJoystickId(10),
      keyboardDevice(keyboard.get()),
      gamecontrollerDevices(10)
{
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

sdli::Device& Processor::getDevice(InputType type, Sint32 id)
{
    switch(type)
    {
    case sdli::InputType::Keyboard:
        return keyboardDevice;
        break;
    case sdli::InputType::Gamecontroller:
        return getControllerDevice(id);
        break;
    default:
        assert(false);
        return keyboardDevice;
        break;
    }
}

void Processor::handleSdlEvents(const SDL_Event& e)
{
    switch(e.type)
    {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
//        printf("Key-input: %d : %d", e.key.keysym.scancode, e.key.state);
        keyboard->push(InputType::Keyboard, e.key.keysym.scancode, e.key.state);
        break;
    case SDL_CONTROLLERDEVICEADDED:
        printf("Controller added: %u\n", e.cdevice.which); // which := hardware-id
        addController(e.cdevice.which);
        break;
    case SDL_CONTROLLERDEVICEREMOVED:
        printf("Controller removed: %u\n", e.cdevice.which);
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        printf("Controller button-down: %u\n", e.cdevice.which); // which := joystick-id
        if(gamecontrollers.at(e.cbutton.which)!=nullptr)
        {
            gamecontrollers.get(e.cbutton.which)->push(InputType::Gamecontroller, e.cbutton.button, e.cbutton.state);
        }
        break;
    case SDL_CONTROLLERBUTTONUP:
        if(gamecontrollers.at(e.cbutton.which)!=nullptr)
        {
            gamecontrollers.get(e.cbutton.which)->push(InputType::Gamecontroller, e.cbutton.button, e.cbutton.state);
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
