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

    printf("%i\n", SDL_GameControllerGetAttached(controller));
    printf("%i\n", SDL_GameControllerEventState(SDL_QUERY));  /* prints 0 */

    rawcontrollers.emplace(std::make_pair(controllerId, controller));

    if(gamecontrollers.find(controllerId)==gamecontrollers.end())
    {
        std::cout << "creating new interface .." << std::endl;
        gamecontrollers.emplace(std::make_pair(controllerId, std::unique_ptr<sdli::Interface>(new sdli::Interface)));
    }
    else
    {
        std::cout << "recycle old interface" <<std::endl;
    }
    getControllerDevice(controllerId);
}

Device& Processor::getControllerDevice(Sint32 controllerId)
{
    if(gamecontrollers.find(controllerId)!=gamecontrollers.end()) // gamecontroller exists and is retrieved again (mostly through addController)
    {
        // Create controller with according interface id
        if(gamecontrollerDevices.find(controllerId)!=gamecontrollerDevices.end())
        {
            std::cout << "recycle null device" << std::endl;
            gamecontrollerDevices.at(controllerId)->setInterface(gamecontrollers.at(controllerId).get());
        }
        else
        {
            std::cout << "create interfaced device" << std::endl;
            gamecontrollerDevices.emplace(std::make_pair(controllerId, std::unique_ptr<sdli::Device>(new sdli::Device(gamecontrollers.at(controllerId).get()))));
        }
    }
    else
    {
        std::cout << "creating null device" << std::endl;
        gamecontrollerDevices.emplace(std::make_pair(controllerId, std::unique_ptr<sdli::Device>(new sdli::Device(nullptr))));
    }

    return *gamecontrollerDevices.at(controllerId);
}

Processor::Processor(unsigned int maxContexts)
    : contextMap(maxContexts),
      keyboard(new sdli::Interface),
      keyboardDevice(keyboard.get())
{
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
        keyboard->push(InputType::Keyboard, e.key.keysym.scancode, e.key.state);
        break;
    case SDL_CONTROLLERDEVICEADDED:
        std::cout << "Controller added " << ":" << e.cdevice.which << std::endl;
        addController(e.cdevice.which);
        break;
    case SDL_CONTROLLERDEVICEREMOVED:
        std::cout << "Controller removed " << ":" << e.cdevice.which << std::endl;
//        SDL_GameControllerClose(rawcontrollers.at(e.cdevice.which));
        break;
    case SDL_CONTROLLERBUTTONDOWN:
        std::cout << "test:" << e.cbutton.which << std::endl;
        if(gamecontrollers.find(e.cbutton.which)!=gamecontrollers.end())
        {
            gamecontrollers.at(e.cbutton.which)->push(InputType::Gamecontroller, e.cbutton.button, e.cbutton.state);
        }
        break;
    case SDL_CONTROLLERBUTTONUP:
        if(gamecontrollers.find(e.cbutton.which)!=gamecontrollers.end())
        {
            gamecontrollers.at(e.cbutton.which)->push(InputType::Gamecontroller, e.cbutton.button, e.cbutton.state);
        }
        break;
    }
}

void Processor::dispatch()
{
    STUB();
}

void Processor::poll()
{
    for(auto& d : devices)
    {
        d.poll();
    }
}

















} // sdli
