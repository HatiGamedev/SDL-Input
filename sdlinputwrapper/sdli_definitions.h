#ifndef SDLI_DEFINITIONS_H
#define SDLI_DEFINITIONS_H

#include <vector>
#include <functional>

namespace sdli {
using InputAction = unsigned int;
using InputAxis = unsigned int;
using ContextId = unsigned int;

const InputAction INVALID_INPUT_ACTION = -1;
const InputAction INVALID_INPUT_AXIS = -1;

enum class CallType
{
    isDown,
    isUp,
    OnRelease,
    OnPress,
    Analog_GT,
    Analog_LT
};

struct LogicDigitalData
{
    bool currentStatus{false};
    bool previousStatus{false};
};

struct LogicAnalogData
{
    float currentStatus{0.0f};
};


enum class InputType
{
    Keyboard,
    Gamecontroller
};

// Forward declarations
class Processor;
class InputContext;
class InputDevice;

using Callback = std::function<void()>;
using CallList = std::vector<Callback>;

} // sdli



#endif // SDLI_DEFINITIONS_H
