#include <gtest/gtest.h>
#include "../sdlinputwrapper.h"
#include "inputaction.h"

enum EInputContext
{
    isPressedContext
};

TEST(InputDevice, defaults)
{
    sdli::Interface device;
    std::unique_ptr<sdli::Context> ctx(new sdli::Context(EInputContext::isPressedContext));

}

TEST(InputDevice, UnmappedDefaults)
{
    sdli::Interface device;
    ASSERT_EQ(false, device.isPressed(EInputAction::Down));
    ASSERT_EQ(false, device.isDown(EInputAction::Down));
    ASSERT_EQ(false, device.isReleased(EInputAction::Down));
    ASSERT_EQ(true, device.isUp(EInputAction::Down));
}


