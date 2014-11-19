#include <gtest/gtest.h>
#include "../util/array.h"
#include "../util/linearallocator.h"

TEST(Util, SDLIBaseArray)
{
    auto array = sdli::util::BaseArray(100);
    array[0] = 1;
    ASSERT_EQ(1, array[0]);
    ASSERT_EQ(1, *array.begin());
}

struct DataType
{
    int idx{0};
    float value{1.0f};
    bool flag{false};
};

TEST(Util, SDLIArray)
{
    unsigned int size = 300000;
    auto array = sdli::util::Array<DataType>(size);
//    ASSERT_EQ(size, array.size());
    array[0].idx = 0;
    array[1].value = 1.0f;
    array[2].flag = false;

    ASSERT_EQ(0, array[0].idx);
    ASSERT_EQ(1.0f, array[1].value);
    ASSERT_EQ(false, array[2].flag);

    auto i=0;
    for(auto it = array.begin(); it!=array.end(); ++it)
    {
        it->idx = i;
        it->value = 10.0f;
        it->flag = true;
        ++i;
    }

    i=0;
    for(auto it = array.begin(); it!=array.end(); ++it)
    {
        ASSERT_EQ(i, it->idx);
        ASSERT_EQ(10.0f, it->value);
        ASSERT_EQ(true, it->flag);
        ++i;
    }
}

TEST(Util, SDLILinearAllocator)
{
    sdli::util::LinearAllocator allocator{100};
    DataType* data = new (allocator.allocate<DataType>()) DataType;

    ASSERT_EQ(DataType{}.idx, data->idx);
    ASSERT_EQ(DataType{}.value, data->value);
    ASSERT_EQ(DataType{}.flag, data->flag);
}
