#ifndef LINEARALLOCATOR_H
#define LINEARALLOCATOR_H

#include "array.h"

namespace sdli {
namespace util {

class LinearAllocator : BaseArray
{
protected:
    char* current;
public:
    LinearAllocator(unsigned int size);
    LinearAllocator(char* begin, char* end);

    LinearAllocator(const LinearAllocator&) =delete;
    LinearAllocator(const LinearAllocator&&) =delete;

    LinearAllocator& operator=(const LinearAllocator&) =delete;
    LinearAllocator& operator=(const LinearAllocator&&) =delete;

    ~LinearAllocator();

    void* allocate(unsigned int size);
    void free(void* ptr);
    void reset(void);

    template<typename T>
    void* allocate()
    {
        return LinearAllocator::allocate(sizeof(T));
    }

    template<typename T>
    static /*constexpr*/ unsigned int BytesOfCount(unsigned int size)
    {
        return sizeof(T) * size;
    }

    template<typename T>
    T* begin()
    {
        return (T*)BaseArray::begin();
    }

    template<typename T>
    T* begin() const
    {
        return (T*)BaseArray::begin();
    }

    template<typename T>
    T* end()
    {
        return (T*)current;
    }

    template<typename T>
    T* end() const
    {
        return (T*)current;
    }

    unsigned int bytes()
    {
        return (pEnd - pBegin);
    }

    template<typename T>
    unsigned int capacity()
    {
        return (pEnd - pBegin)/sizeof(T);
    }

    unsigned int size() const
    {
        return (current - pBegin);
    }

    template<typename T>
    unsigned int size() const
    {
        return (current - pBegin) / sizeof(T);
    }

};



} // util
} // sdli

#endif // LINEARALLOCATOR_H
