#ifndef CALLBACK_H
#define CALLBACK_H

namespace sdli {
namespace util {

template<typename T> class Lambda {};

template<typename Out, typename... In>
class Lambda<Out(In...)>
{
    void* functionLambda;
    Out(*executionLambda)(void*, In...);
public:

    Lambda()
        : functionLambda(nullptr), executionLambda(nullptr)
    {}

    template<typename T>
    Lambda(const T& l)
        : functionLambda(new T(l)),
          executionLambda([](void* l, In... args) -> Out
                          {
                                return ((T*)l)->operator()(args...);
                          })
    {}

    Lambda(const Lambda&) =default;
    Lambda(const Lambda&&) =delete;

    Lambda<Out(In...)>& operator=(const Lambda<Out(In...)>&) = delete;
    Lambda<Out(In...)>& operator=(const Lambda<Out(In...)>&&) =delete;

    template<typename T> Lambda<Out(In...)>& operator=(const T& l)
    {
        functionLambda = new T(l);
        executionLambda = [](void* l, In... args) -> Out
        {
            return ((T*)l)->operator()(args...);
        };

        return *this;
    }

    Out operator()(In... args)
    {
        return executionLambda(functionLambda, args...);
    }
};

} // util
} // sdli

#endif // CALLBACK_H
