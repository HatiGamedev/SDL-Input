#ifndef ARRAY_H
#define ARRAY_H


namespace sdli {
namespace util {

class BaseArray
{
protected:
    char* memory;

    char* pBegin;
    char* pEnd;
public:
    BaseArray(unsigned int size);
    ~BaseArray();

    char& operator[](unsigned int idx);

    char* begin();
    char* end();

    unsigned int size() const;
};

template<typename T>
class Array : BaseArray
{
public:
    using Iterator = T*;

    Array(unsigned int size)
        : BaseArray(sizeof(T)*size)
    {

    }

    T& operator[](unsigned int idx)
    {
        return *(T*)(&BaseArray::operator [](idx*sizeof(T)));
    }

    T* begin()
    {
        return (T*)(BaseArray::pBegin);
    }

    T* end()
    {
        return (T*)(BaseArray::pEnd);
    }

    unsigned int size() const
    {
        return (pEnd - pBegin)/sizeof(T);
    }
};

} // util
} // sdli

#endif // ARRAY_H
