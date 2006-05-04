#ifndef _INCLUDED_SRCONFLICT_
#define _INCLUDED_SRCONFLICT_

class Symbol;
class Production;

class SRConflict
{
    Symbol const *d_symbol;
    unsigned d_state;
    Production const *d_production;

    public:
        SRConflict()
        {}
        SRConflict(Symbol const *symbol, unsigned state, 
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
