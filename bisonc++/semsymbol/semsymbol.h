#ifndef INCLUDED_SEMSYMBOL_
#define INCLUDED_SEMSYMBOL_

#include "../sembase/sembase.h"
class Symbol;

class SemSymbol: public SemBase
{
    Symbol *d_symbol;

    public:
        SemSymbol(Symbol *symbol);    // not owned by SemSymbol!
        operator Symbol *() const;
};

inline SemSymbol::SemSymbol(Symbol *symbol)
:
    SemBase(Tag::SYMBOL),
    d_symbol(symbol)
{}

inline SemSymbol::operator Symbol *() const
{
    return d_symbol;
}

template <>
struct Type<SemEnum::Tag::SYMBOL>
{
    typedef SemSymbol const &conversionType;
    typedef Symbol *semType;
};

        
#endif
