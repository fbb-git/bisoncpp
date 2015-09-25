#include "next.ih"

size_t Next::addToKernel(Next::Vector &next,
                        Symbol const *symbol, size_t stateItemOffset)
{
    Iterator it = find_if(
                    next.begin(), next.end(), 
                    [&](Next const &next)
                    {
                        return next.d_symbol == symbol;
                    }
                );
    
    it->d_kernel.push_back(stateItemOffset);
    return it - next.begin();
}
