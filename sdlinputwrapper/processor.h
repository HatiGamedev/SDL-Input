#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <map>
#include <memory>

#include <SDL2/SDL_events.h>
#include "keyboardinterface.h"
#include "mouseinterface.h"
#include "sdli_definitions.h"
#include "device.h"
#include "util/array.h"
#include "util/indexmap.h"

namespace sdli {

enum ProcessorEventFlags
{
    ControllerConnect   = 1<<0,
    ControllerButtons   = 1<<1,

    Keyboard            = 1<<2,


    BASIC               = ControllerConnect | ControllerButtons | Keyboard,
    ALL                 = ControllerConnect | ControllerButtons | Keyboard,
};

class Processor
{
    uint32_t sdlEventFlag = sdli::ProcessorEventFlags::BASIC;

    /// TODO: proposal: linearilize
    sdli::util::Array<sdli::Context> contextMap;

//    std::unique_ptr<sdli::Interface> keyboard;
    std::unique_ptr<sdli::KeyboardInterface> keyboard;
    sdli::Device keyboardDevice;


    std::unique_ptr<sdli::MouseInterface> mouse;
    sdli::Device mouseDevice;


    sdli::util::IndexMap<Sint32, std::unique_ptr<sdli::Interface>> gamecontrollerInterfaces;

    sdli::util::IndexMap<Sint32, Sint32> hardwareIdToJoystickId;

    sdli::util::IndexMap<Sint32, std::unique_ptr<sdli::Device>> gamecontrollerDevices;

    std::vector<sdli::Device*> devices;

private:
    sdli::Interface* getControllerInterface(Sint32 controllerId);
    void addController(Sint32 controllerId);
    sdli::Device& getControllerDevice(Sint32 hardwareId);

public:
    Processor(unsigned int maxContexts);

    sdli::Context* createContext(const sdli::ContextId& contextId);
    sdli::Context* getContext(const sdli::ContextId& contextId);

    sdli::Device& getKeyboard();
    sdli::Device& getMouse();
    sdli::Device& getGamecontroller(unsigned int id);
    sdli::Device& getDevice(sdli::InputType type);

    void deactivateDevice(const sdli::Device& d);

    unsigned int controllers() {return SDL_NumJoysticks();}

    void handleSdlEvents(const SDL_Event& e);

    void dispatch();
    void poll();

    void swap();


};

} // sdli

#endif // PROCESSOR_H
