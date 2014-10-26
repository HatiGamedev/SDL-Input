#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include "../sdlinputwrapper.h"
#include "sdl_testenviroment.h"
#include "inputaction.h"
#include <memory>

//GTEST_ASSERT_EQ(false, device.isPressed(InputAction::Up));

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

#include <memory>

struct Test
{
    bool isActive;
};

struct TestHandle
{
    Test* mdata{nullptr};
public:
    TestHandle(){}

    // removes copy
    TestHandle(const TestHandle&) =delete;
    TestHandle& operator=(const TestHandle&) =delete;

    bool isActive() const;
};

class Proc
{
    TestHandle something;
public:
    TestHandle& get();
    void createNew();
};


int main(int argc, char** argv)
{

    Proc proc;
    auto& test = proc.get();
    std::cout << test.isActive() << std::endl;

    proc.createNew();
    std::cout << test.isActive() << std::endl;

//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::AddGlobalTestEnvironment(new SDL_TestEnviroment);




//    return RUN_ALL_TESTS();
}





TestHandle& Proc::get()
{
    return something;
}

void Proc::createNew()
{
    something.mdata = new Test;
    something.mdata->isActive = true;

}


bool TestHandle::isActive() const
{
    if(mdata)
    {
        return mdata->isActive;
    }
    return false;
}
