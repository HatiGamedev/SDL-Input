#ifndef INDEXMAP_H
#define INDEXMAP_H

#include "array.h"
#include "linearallocator.h"
#include <cassert>

namespace sdli {
namespace util {

template<typename IdxType, typename T>
class IndexMap
{
    struct Index
    {
        IdxType idx;
        T* data;
    };

    LinearAllocator indices; //TODO: replace by stack allocator (to enable easy-removal)
    LinearAllocator data;

public:
    IndexMap(unsigned int size)
        : indices(LinearAllocator::BytesOfCount<Index>(size)),
          data(LinearAllocator::BytesOfCount<T>(size))
    {
    }

    IndexMap(unsigned int size, void* begin, void* end)
        : indices(begin, begin+LinearAllocator::BytesOfCount<Index>(size)),
          data(begin+LinearAllocator::BytesOfCount<Index>(size)+1,
               begin+LinearAllocator::BytesOfCount<Index>(size)+LinearAllocator::BytesOfCount<T>(size))
    {
        assert(begin
               +LinearAllocator::BytesOfCount<Index>(size)
               +LinearAllocator::BytesOfCount<T>(size) <= end);
    }

    template<typename... Args>
    void emplace(IdxType idx, Args... args)
    {
        assert(at(idx)==nullptr);
        auto i = new (indices.allocate<Index>()) Index;
        i->idx = idx;
        i->data = new (data.allocate<T>()) T(args...);
    }

    T* at(IdxType idx) const
    {
        auto it = indices.begin<Index>();
        auto end = indices.end<Index>();
        for(;it!=end;++it)
        {
            if(it->idx == idx)
            {
                return it->data;
            }
        }
        return nullptr;
    }

    T& get(IdxType idx) const
    {
        T* data = at(idx);
        assert(data!=nullptr);
        return *data;
    }

    Index* begin()
    {
        return indices.begin<Index>();
    }

    Index* end()
    {
        return indices.end<Index>();
    }

    Index* begin() const
    {
        return indices.begin<Index>();
    }

    Index* end() const
    {
        return indices.end<Index>();
    }

    T* dataBegin()
    {
        return data.begin<T>();
    }

    T* dataEnd()
    {
        return data.end<T>();
    }

    void clear()
    {
        indices.reset();
        data.reset();
    }

    void move(IdxType currentIdx, IdxType newIdx)
    {
        assert(at(currentIdx)!=nullptr); // must be in
        assert(at(newIdx)==nullptr); // must not be in

        auto it = indices.begin<Index>();
        auto end = indices.end<Index>();
        for(;it!=end;++it)
        {
            if(it->idx == currentIdx)
            {
                it->idx = newIdx;
                break;
            }
        }
    }

    unsigned int size() const
    {
        return indices.size<Index>();
    }

    static constexpr unsigned int BytesOfIndexMap(unsigned int size)
    {
        return LinearAllocator::BytesOfCount<Index>(size)+LinearAllocator::BytesOfCount<T>(size);
    }
};

} // util
} // sdli

#endif // INDEXMAP_H
