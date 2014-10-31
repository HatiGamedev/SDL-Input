#ifndef CALLBACK_H
#define CALLBACK_H
#include <cassert>
namespace sdli {
namespace util {

/**
 * Supports (capturing-) lambdas and raw C functions interchangeably
 */

template<typename T> class Lambda {};

template<typename Out, typename... In>
class Lambda<Out(In...)>
{
    void* functionLambda;
    Out(*rawCFunction)(In...);
    Out(*executionLambda)(void*, In...);
public:

    Lambda()
        : functionLambda(nullptr), rawCFunction(nullptr), executionLambda(nullptr)
    {}

    template<typename T>
    Lambda(const T& l)
        : functionLambda(new T(l)),
          rawCFunction(nullptr),
          executionLambda([](void* l, In... args) -> Out
                          {
                                return ((T*)l)->operator()(args...);
                          })
    {}

    Lambda(Out (*f)(In...))
        : functionLambda(nullptr),
          rawCFunction(f),
          executionLambda(nullptr)
    {

    }

    Lambda(const Lambda&) =default;
    Lambda(const Lambda&& o)
        : functionLambda(std::move(o.functionLambda)),
          rawCFunction(std::move(o.rawCFunction)),
          executionLambda(std::move(o.executionLambda))
    {
    }

    Lambda<Out(In...)>& operator=(const Lambda<Out(In...)>&) = delete;
    Lambda<Out(In...)>& operator=(const Lambda<Out(In...)>&&) =delete;

    template<typename T> Lambda<Out(In...)>& operator=(const T& l)
    {
        if(this != &l)
        {
            functionLambda = new T(l);
            rawCFunction = l.rawCFunction;
            executionLambda = [](void* l, In... args) -> Out
            {
                return ((T*)l)->operator()(args...);
            };
        }
        return *this;
    }

    Out operator()(In... args) const
    {
        assert(executionLambda || rawCFunction);
        if(executionLambda)
            return executionLambda(functionLambda, args...);
        if(rawCFunction)
            return rawCFunction(args...);
    }
};

} // util
} // sdli

#endif // CALLBACK_H
