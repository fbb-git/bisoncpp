#include "state.ih"

size_t State::nextOn(Symbol const *symbol) const
{
    Next::ConstIter iter = nextFind(symbol);

    return iter == d_nextVector.end() ? string::npos : iter->next();
}
