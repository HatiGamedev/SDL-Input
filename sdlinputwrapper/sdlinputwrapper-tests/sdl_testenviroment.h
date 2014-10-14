#ifndef SDL_TESTENVIROMENT_H
#define SDL_TESTENVIROMENT_H

#include <gtest/gtest.h>

class SDL_TestEnviroment : public ::testing::Environment
{
    // Environment interface
public:
    void SetUp();
    void TearDown();
};


#endif // SDL_TESTENVIROMENT_H
