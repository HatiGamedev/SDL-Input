#include "array.h"
#include <cassert>
#include <cstring>

namespace sdli {
namespace util {

BaseArray::BaseArray(unsigned int size)
    : pBegin(new char[size]),
      pEnd(pBegin+sizeof(char)*size)
{
    assert(size!=0);
    std::memset(pBegin, 0, size);
}

BaseArray::BaseArray(char* begin, char* end)
    : pBegin(begin),
      pEnd(end)
{
    assert(size()!=0);
    std::memset(pBegin, 0, size());
}

BaseArray::~BaseArray()
{
    delete [] pBegin;
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

char* BaseArray::begin()
{
    return pBegin;
}

char*BaseArray::begin() const
{
    return pBegin;
}

char* BaseArray::end()
{
    return pEnd;
}

char*BaseArray::end() const
{
    return pEnd;
}

unsigned int BaseArray::size() const
{
    return pEnd - pBegin;
}

} // util
} // sdli
