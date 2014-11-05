#ifndef MAP_H
#define MAP_H

#include "array.h"
#include <cassert>

namespace sdli {
namespace util {
/** Not yet implemented **/
template<typename _IdxType, typename _To>
class IndexMap
{
protected:
    struct IndexedTo
    {
        _IdxType idx;
        _To* data;
    };

    sdli::util::Array<IndexedTo> keys;

public:
    IndexMap(unsigned int keySize)
        : keys(keySize)
    {
        assert(false);
    }

    _To& operator[](const _IdxType& idx)
    {
        assert(false);
        for(auto it=keys.begin();it!=keys.end();++it)
        {
            if(idx == it->idx)
            {
                return *it->data;
            }
        }
    }
};

} // util
} // sdli

#endif // MAP_H
