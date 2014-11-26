#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <map>
#include <memory>

#include <SDL2/SDL_events.h>

#include "sdli_definitions.h"
#include "device.h"
#include "util/array.h"

namespace sdli {

class Processor
{
    /// TODO: proposal: linearilize
//    std::map<sdli::ContextId, std::unique_ptr<sdli::Context>> contextMap; /// TODO: using array to access contexts
    sdli::util::Array<sdli::Context> contextMap;

    std::unique_ptr<sdli::Interface> keyboard;
    std::map<Sint32, std::unique_ptr<sdli::Interface>> gamecontrollers; /// TODO: using array to access interfaces
    std::map<Sint32, SDL_GameController*> rawcontrollers;

    sdli::Device keyboardDevice;
    std::map<Sint32, std::unique_ptr<sdli::Device>> gamecontrollerDevices; /// TODO: using array to access devices

    std::vector<sdli::Device> devices;

private:
    void addController(Sint32 controllerId);
    sdli::Device& getControllerDevice(Sint32 controllerId);

public:
    Processor(unsigned int maxContexts);

    sdli::Context* createContext(const sdli::ContextId& contextId);
    sdli::Context* getContext(const sdli::ContextId& contextId);

    sdli::Device& getDevice(sdli::InputType type, Sint32 id);
    void deactivateDevice(const sdli::Device& d);


    void handleSdlEvents(const SDL_Event& e);

    void dispatch();
    void poll();

    void swap();


};

} // sdli

#endif // PROCESSOR_H
