#include "state.ih"

Next::ConstIter State::nextFind(Symbol const *symbol) const
{
    return find_if(d_nextVector.begin(), d_nextVector.end(), 
                   FnWrap::unary(Next::hasSymbol, symbol));
}
