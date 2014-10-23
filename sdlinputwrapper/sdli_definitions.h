#ifndef SDLI_DEFINITIONS_H
#define SDLI_DEFINITIONS_H

namespace sdli {
using InputAction = unsigned int;
using InputAxis = unsigned int;
using ContextId = unsigned int;

struct LogicDigitalData
{
    bool currentStatus{false};
    bool previousStatus{false};
};

struct LogicAnalogData
{
    float currentStatus{0.0f};
};


} // sdli



#endif // SDLI_DEFINITIONS_H
