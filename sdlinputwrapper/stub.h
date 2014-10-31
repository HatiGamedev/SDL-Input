#ifndef STUB_H
#define STUB_H

#ifdef __clang__
#   include <iostream>
#   define SDLI_STUB(X) std::printf("%s:%s\n", __PRETTY_FUNCTION__, #X)
#else
#   define SDLI_STUB(X) (void)0
#endif

#endif // STUB_H
