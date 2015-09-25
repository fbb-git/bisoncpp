#include "state.ih"

Next::ConstIter State::nextFind(Symbol const *symbol) const
{
    return find_if(
                d_nextVector.begin(), d_nextVector.end(), 
                [=](Next const &next)
                {
                    return next.hasSymbol(symbol);
                }
            );
              //     FnWrap::unary(Next::hasSymbol, symbol));
}
