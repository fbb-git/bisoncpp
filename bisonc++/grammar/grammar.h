#ifndef _INCLUDED_GRAMMAR_
#define _INCLUDED_GRAMMAR_

#include <set>

#include "../symbol/symbol.h"
#include "../production/production.h"

class Grammar
{
    typedef std::set<Symbol const *> SymbolSet;

    SymbolSet    d_derivable;           // used when testing whether the start
                                        // symbol derives any sentences
    SymbolSet    d_inspecting;          // (same, see derivable.cc)

    public:
        void deriveSentence();

    private:
        bool derivable(Symbol const *symbol);

        bool isDerivable(Production const *prod);
        bool becomesDerivable(Production const *prod);
};

#endif

