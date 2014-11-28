#include "sdli_axis.h"


bool operator==(const sdli::SDL_Axis& a1, const sdli::SDL_Axis& a2)
{

        if(a1.type != a2.type)
        {
            return false;
        }

        bool val = false;
        switch(a1.type)
        {
        case sdli::SDL_Axis::Type::Keyboard:
            val = (a1.axis.rawNegative == a2.axis.rawNegative) && (a1.axis.rawPositive == a2.axis.rawPositive);
            break;
        case sdli::SDL_Axis::Type::GameController:
            val = (a1.rawControllerAxis == a2.rawControllerAxis);
            break;
        }

        return val;
}
