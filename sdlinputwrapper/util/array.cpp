#include "array.h"
#include <cassert>
#include <cstring>

namespace sdli {
namespace util {

BaseArray::BaseArray(unsigned int size)
    : memory(new char[size]),
      pBegin(&memory[0]),
      pEnd(&memory[0]+sizeof(char)*size)
{
    assert(size!=0);
    std::memset(memory, 0, size);
}

BaseArray::BaseArray(char* begin, char* end)
    : memory(begin),
      pBegin(begin),
      pEnd(end)
{
    assert(size()!=0);
    std::memset(memory, 0, size());
}

BaseArray::~BaseArray()
{
    delete [] memory;
}

char& BaseArray::operator[](unsigned int idx)
{
    assert(pBegin + idx < pEnd);
    return *(pBegin + idx);
}

const char&BaseArray::operator[](unsigned int idx) const
{
    return *(pBegin + idx);
}

char*BaseArray::begin()
{
    return pBegin;
}

char*BaseArray::end()
{
    return pEnd;
}

unsigned int BaseArray::size() const
{
    return pEnd - pBegin;
}

} // util
} // sdli
