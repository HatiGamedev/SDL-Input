#include "device.h"
#include "interface.h"
#include "context.h"
#include <iostream>

#define _DEVICE_GUARD_(x, defVal) if(!(x)) { return defVal;}

namespace sdli {


void Device::setInterface(Interface* interface)
{
    this->interface = interface;
}

Device::Device(Interface* interface)
    : interface(interface)
{
}

void Device::pushContext(Context* ctx)
{
    contextStack_.push(ctx);
}

Context* Device::currentContext()
{
    if(contextStack_.empty())
    {
        return nullptr;
    }

    return contextStack_.top();
}

Context* Device::popContext()
{
    if(contextStack_.empty())
    {
        return nullptr;
    }

    auto ctx = contextStack_.top();
    contextStack_.pop();
    return ctx;
}

void Device::poll()
{
    _DEVICE_GUARD_(interface, ;);
    assert(!contextStack_.empty());
    interface->poll(*contextStack_.top());
}

void Device::dispatch()
{
    _DEVICE_GUARD_(interface, ;);
    assert(!contextStack_.empty());
    interface->dispatch(*contextStack_.top());
}

float Device::getAxis(InputAxis axis)
{
    _DEVICE_GUARD_(interface, ::sdli::RANGE_UNDEFINED);
    return interface->getRange(axis);
}

bool Device::isPressed(InputAction action)
{
    _DEVICE_GUARD_(interface, ::sdli::IS_PRESSED_UNDEFINED);
    return interface->isPressed(action);
}

bool Device::isReleased(InputAction action)
{
    _DEVICE_GUARD_(interface, ::sdli::IS_RELEASED_UNDEFINED);
    return interface->isReleased(action);
}

bool Device::isDown(InputAction action)
{
    _DEVICE_GUARD_(interface, ::sdli::IS_DOWN_UNDEFINED);
    return interface->isDown(action);
}

bool Device::isUp(InputAction action)
{
    _DEVICE_GUARD_(interface, ::sdli::IS_UP_UNDEFINED);
    return interface->isUp(action);
}

void Device::swap()
{
    _DEVICE_GUARD_(interface,;);
    interface->swap();
}

} // sdli
