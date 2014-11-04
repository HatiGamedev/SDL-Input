#ifndef STUB_H
#define STUB_H

#ifdef __llvm__
#   define STUB(X) std::printf("[%s] %s:%s\n", __FILE__, __PRETTY_FUNCTION__, #X)
#elif __GNUC__
#   define STUB(X) std::printf("[%s] %s:%s\n", __FILE__, __PRETTY_FUNCTION__, #X)
#else
#   define STUB(X) (void)0
#endif

#endif // STUB_H
