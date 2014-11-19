#ifndef ARRAY_H
#define ARRAY_H


namespace sdli {
namespace util {

class BaseArray
{
protected:
    char* pBegin;
    char* pEnd;
public:
    BaseArray(unsigned int size);
    BaseArray(char* begin, char* end);
    ~BaseArray();

    char& operator[](unsigned int idx);

    const char& operator[](unsigned int idx) const;

    char* begin();
    char* end();

    unsigned int size() const;
};

template<typename T>
class Array : BaseArray
{
protected:

    T* memoryPtr(unsigned int idx) const
    {
        return (T*)(&BaseArray::operator [](idx*sizeof(T)));
    }

public:
    using Iterator = T*;

    Array(unsigned int size)
        : BaseArray(sizeof(T)*size)
    {

    }

    Array(T* begin, T* end)
        : BaseArray((char*)begin, (char*)end)
    {
    }

    T& operator[](unsigned int idx)
    {
        return *(T*)(&BaseArray::operator [](idx*sizeof(T)));
    }

    const T& operator[](unsigned int idx) const
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

    template<typename... Args>
    void emplace_at(unsigned int idx, Args... args)
    {
        new (memoryPtr(idx)) T(args...);
    }
};

} // util
} // sdli

#endif // ARRAY_H
