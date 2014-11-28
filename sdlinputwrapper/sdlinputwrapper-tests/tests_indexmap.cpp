#include <gtest/gtest.h>
#include "../util/indexmap.h"

struct Data
{
    float x{0.0f}, y{0.0f};
    short state{-1};
};



TEST(Util, IndexMap)
{
    sdli::util::IndexMap<unsigned int, Data> map(10);

    map.emplace(1);

    EXPECT_EXIT(map.emplace(1), ::testing::KilledBySignal(SIGABRT), "");


    ASSERT_EQ(map.at(1)->state, -1);
    ASSERT_EQ(map.at(1)->x, 0.0f);
    ASSERT_EQ(map.at(1)->y, 0.0f);

    auto i = map.at(1);
    i->state = 100;

    ASSERT_EQ(map.at(1)->state, 100);

    map.emplace(10000);
    i = map.at(10000);

    ASSERT_EQ(i->state, -1);
    ASSERT_EQ(i->x, 0.0f);
    ASSERT_EQ(i->y, 0.0f);

    auto it = map.begin();
    auto end = map.end();

    int count=0;
    for(;it!=end;++it)
    {
        ASSERT_NE(it, nullptr);
        count++;
    }
    ASSERT_EQ(count, 2);

}

TEST(Util, IndexMapMax)
{
    const unsigned int count = 10;

    sdli::util::IndexMap<unsigned int, Data> map(count);

    for(int i=0;i<count;++i)
    {
        map.emplace(i);
        auto& d = map.get(i);
        d.x = 1.0f*i;
        d.y = 0.5f*i;
        d.state = 10 * i;
    }

    for(int i=0;i<count;++i)
    {
        ASSERT_NE(map.at(i), nullptr);
    }


}
