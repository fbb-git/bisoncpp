#ifndef _INCLUDED_GRAMMAR_
#define _INCLUDED_GRAMMAR_

#include <set>

#include "../symbol/symbol.h"
#include "../production/production.h"

class Grammar
{
    typedef std::set<Symbol const *> SymbolSet;

    SymbolSet    d_derivable;
    SymbolSet    d_inspecting;

    public:
        void deriveSentence();

    private:
        bool derivable(Symbol const *symbol);

        static bool isDerivable(Production const *prod, Grammar &object);
        static bool notRemovable(Symbol const *symbol, Grammar &object);
        static bool notDerivable(Symbol const *symbol, Grammar &object);
        static bool becomesDerivable(Production const *prod, Grammar &object);
};

inline bool Grammar::notDerivable(Symbol const *symbol, Grammar &object) 
{
    return !object.derivable(symbol);
}

inline bool Grammar::notRemovable(Symbol const *symbol, Grammar &object)
{
    return                  // not removable if:
                            // currently testing 
        object.d_inspecting.find(symbol) != object.d_inspecting.end()
        ||                  // or a non-removable non-terminal
        (symbol->isNonTerminal() &&
            object.d_derivable.find(symbol) == object.d_derivable.end())
        ;
}

#endif

