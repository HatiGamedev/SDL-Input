#include <gtest/gtest.h>
#include "../sdlinputwrapper.h"
#include "inputaction.h"

enum EInputContext
{
    ModShiftContext
};

TEST(InputDevice, defaults)
{
//    sdli::Interface device;
    auto processor = std::unique_ptr<sdli::Processor>(new sdli::Processor(2));
    processor->createContext(EInputContext::ModShiftContext);

}

TEST(InputDevice, UnmappedDefaults)
{
    sdli::Interface device;
    ASSERT_EQ(false, device.isPressed(EInputAction::Down));
    ASSERT_EQ(false, device.isDown(EInputAction::Down));
    ASSERT_EQ(false, device.isReleased(EInputAction::Down));
    ASSERT_EQ(true, device.isUp(EInputAction::Down));
}


