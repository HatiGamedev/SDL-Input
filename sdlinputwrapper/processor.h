#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <map>
#include <memory>

#include <SDL2/SDL_events.h>

#include "sdli_definitions.h"
#include "device.h"
#include "util/array.h"
#include "util/indexmap.h"

namespace sdli {

class Processor
{
    /// TODO: proposal: linearilize
//    std::map<sdli::ContextId, std::unique_ptr<sdli::Context>> contextMap; /// TODO: using array to access contexts
    sdli::util::Array<sdli::Context> contextMap;

    std::unique_ptr<sdli::Interface> keyboard;
    sdli::util::IndexMap<Sint32, std::unique_ptr<sdli::Interface>> gamecontrollers;
//    std::map<Sint32, std::unique_ptr<sdli::Interface>> gamecontrollers; /// TODO: using array to access interfaces

    sdli::util::IndexMap<Sint32, Sint32> hardwareToJoystickId;

    sdli::Device keyboardDevice;

    sdli::util::IndexMap<Sint32, std::unique_ptr<sdli::Device>> gamecontrollerDevices;

    std::vector<sdli::Device*> devices;

private:
    void addController(Sint32 controllerId);
    sdli::Device& getControllerDevice(Sint32 hardwareId);

public:
    Processor(unsigned int maxContexts);

    sdli::Context* createContext(const sdli::ContextId& contextId);
    sdli::Context* getContext(const sdli::ContextId& contextId);

    sdli::Device& getKeyboard();
    sdli::Device& getGamecontroller(unsigned int id);

    void deactivateDevice(const sdli::Device& d);

    unsigned int controllers() {return SDL_NumJoysticks();}

    void handleSdlEvents(const SDL_Event& e);

    void dispatch();
    void poll();

    void swap();


};

} // sdli

#endif // PROCESSOR_H
