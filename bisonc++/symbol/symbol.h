#ifndef _INCLUDED_SYMBOL_
#define _INCLUDED_SYMBOL_

#include <ostream>

#include "../element/element.h"
#include "../firstset/firstset.h"

class Symbol: public Element
{
    std::string const d_name;
    std::string d_stype;        // Type assigned by explicit symbol type 
                                // association, e.g. %type <int> symbol
                                // but there's also a type association with
                                // symbols when no %union is specified. In
                                // that case it's either the default (int) or
                                // %stype-defined type.
    
    int d_type;
    mutable bool d_used;
    
    public:
        enum Type
        {
            UNDETERMINED        = 0,
            CHAR_TERMINAL       = 1,
            SYMBOLIC_TERMINAL   = 2,
            NON_TERMINAL        = 4,
            RESERVED            = 8,
        };

        ~Symbol();

        static char const *showType(Symbol const *symbol)
        {
            return symbol->d_type == NON_TERMINAL ? "Non-terminal" 
                                                  : "Terminal";
        }

        Symbol(std::string const &name, Type t, std::string const &type = "");

        bool isTerminal() const
        {
            return !(d_type & NON_TERMINAL);
        }
        bool isSymbolic() const
        {
            return d_type & SYMBOLIC_TERMINAL;
        }
        bool isNonTerminal() const
        {
            return d_type & NON_TERMINAL;
        }
        bool isUndetermined() const
        {
            return d_type == UNDETERMINED;
        }
        bool isUsed() const
        {
            return d_used;
        }
        bool isReserved() const
        {
            return d_type & RESERVED;
        }
        void setReserved()
        {
            d_type |= RESERVED;
        }
        void used() const       // d_used is mutable.
        {
            d_used = true;
        }
        void setType(Type type)
        {
            d_type = type;
        }
        void setStype(std::string const &stype)
        {
            d_stype = stype;
        }
        std::string const &sType() const
        {
            return d_stype;
        }
        std::string const &name() const
        {
            return d_name;
        }
        virtual FirstSet const &firstSet() const = 0;

        virtual std::string const &display() const
        {
            return name();
        }

        static void displaySymbol(Symbol const *sp);
};

#endif
