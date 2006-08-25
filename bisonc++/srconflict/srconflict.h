#ifndef _INCLUDED_SRCONFLICT_
#define _INCLUDED_SRCONFLICT_

    // for size_t:
#include <cstddef>

class Symbol;
class Production;

class SRConflict
{
    Symbol const *d_symbol;
    size_t/*unsigned*/ d_state;
    Production const *d_production;

    public:
        SRConflict()
        {}
        SRConflict(Symbol const *symbol, size_t/*unsigned*/ state, 
                   Production const *production)
        :
            d_symbol(symbol),
            d_state(state),
            d_production(production)
        {}
        static void show(SRConflict const &conflict);
    private:
};

        
#endif
