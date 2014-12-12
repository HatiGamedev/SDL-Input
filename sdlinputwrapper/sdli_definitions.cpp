#include "sdli_definitions.h"


namespace sdli
{

float clamp(float cur, float min, float max)
{
    return std::max(std::min(cur, max), min);
}

bool isPressed(const LogicDigitalData& d)
{
    return d.currentStatus
            && d.previousStatus != d.currentStatus;
}

bool isReleased(const LogicDigitalData& d)
{
    return !d.currentStatus
            && d.previousStatus != d.currentStatus;
}

bool isDown(const LogicDigitalData& d)
{
    return d.currentStatus;
}

bool isUp(const LogicDigitalData& d)
{
    return !d.currentStatus;
}

}
