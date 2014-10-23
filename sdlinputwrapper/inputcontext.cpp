#include "inputcontext.h"

namespace sdli
{

InputContext::InputContext(const ContextId& contextId)
    : contextId_(contextId)
{
}

ContextId InputContext::id() const
{
    return this->contextId_;
}












} // sdli
