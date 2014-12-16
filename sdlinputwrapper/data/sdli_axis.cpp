#include "sdli_axis.h"


bool operator==(const sdli::SDL_Axis& a1, const sdli::SDL_Axis& a2)
{

        if(a1.deviceType != a2.deviceType)
        {
            return false;
        }

        bool val = false;
        switch(a1.deviceType)
        {
        case sdli::SDL_Axis::Type::Keyboard:
            val = (a1.axis.rawNegative == a2.axis.rawNegative) && (a1.axis.rawPositive == a2.axis.rawPositive);
            break;
        case sdli::SDL_Axis::Type::Gamecontroller:
            val = (a1.rawControllerAxis == a2.rawControllerAxis) || ((a1.axis.rawNegative == a2.axis.rawNegative) && (a1.axis.rawPositive == a2.axis.rawPositive));
            break;
        case sdli::SDL_Axis::Type::Mouse:
            val = (a1.rawMouseAxis == a2.rawMouseAxis);
            break;
        }

        return val;
}
