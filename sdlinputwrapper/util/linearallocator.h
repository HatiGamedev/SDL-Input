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

    template<typename T>
    LinearAllocator(unsigned int max_count)
        : BaseArray(LinearAllocator::BytesOfCount<T>(max_count)),
          current(pBegin)
    {}

    LinearAllocator(const LinearAllocator&) =delete;
    LinearAllocator(const LinearAllocator&&) =delete;

    LinearAllocator& operator=(const LinearAllocator&) =delete;
    LinearAllocator& operator=(const LinearAllocator&&) =delete;

    void* allocate(unsigned int size);
    void free(void* ptr);
    void reset(void);

    template<typename T>
    void* allocate()
    {
        return LinearAllocator::allocate(sizeof(T));
    }

    template<typename T>
    static constexpr unsigned int BytesOfCount(unsigned int size)
    {
        return sizeof(T) * size;
    }
};

} // util
} // sdli

#endif // LINEARALLOCATOR_H
