#include "sdli_definitions.h"
#include <algorithm>
#include <math.h>

namespace sdli
{

float clamp(float cur, float min_, float max_)
{
    return std::max(std::min(cur, max_), min_);
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
