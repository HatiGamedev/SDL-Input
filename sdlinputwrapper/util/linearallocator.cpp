#include "linearallocator.h"
#include <cassert>
#include <cstring>

namespace sdli {
namespace util {

LinearAllocator::LinearAllocator(unsigned int size)
    : BaseArray(size),
      current(BaseArray::pBegin)
{
}

LinearAllocator::LinearAllocator(char* begin, char* end)
    : BaseArray(begin, end),
      current(BaseArray::pBegin)
{
}

void* LinearAllocator::allocate(unsigned int size)
{
    assert(size < (pEnd - current));
    auto mem = current;

    current += size;

    return mem;
}

void LinearAllocator::reset()
{
    memset(BaseArray::pBegin, 0, BaseArray::size());
    current = BaseArray::pBegin;
}

} // util
} // sdli
