#include "state.ih"

Next::ConstIter State::nextFind(Symbol const *symbol) const
{
    return find_if(d_nextVector.begin(), d_nextVector.end(), 
                   FnWrap1c<Next const &, Symbol const *, bool>(Next::hasSymbol, 
                                                              symbol));
}
