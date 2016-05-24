#ifndef _INCLUDED_SYMBOL_
#define _INCLUDED_SYMBOL_

#include <ostream>
#include <vector>

#include "../element/element.h"
#include "../firstset/firstset.h"

class Symbol: public Element
{
    public:
        typedef std::vector<Symbol const *>  Vector;
    
        enum Type
        {
            UNDETERMINED        = 0,
            CHAR_TERMINAL       = 1,
            SYMBOLIC_TERMINAL   = 2,
            NON_TERMINAL        = 4,
            RESERVED            = 8,
        };

    private:
        std::string const d_name;
                                // Name of the symbol, assigned at
                                // construction time, returned by name()

        std::string d_stype;        
                                // Type assigned by explicit symbol type 
                                // association, e.g. %type <int> symbol but
                                // there's also a type association with
                                // symbols when no %union or %polymorphic is
                                // specified. In that case it's either the
                                // default (int) or %stype-defined type.
    
        int d_type;             // type of the symbol using the enum values of
                                // the above Type enum. Type's values are bit
                                // values, and multiple values may therefore
                                // be assigned.

        mutable bool d_used;    // Set to true once the symbol has actually
                                // been used in the grammar.

    public:
        ~Symbol();

        bool isNonTerminal() const;
        bool isReserved() const;
        bool isSymbolic() const;
        bool isTerminal() const;
        bool isUndetermined() const;
        bool isUsed() const;

        std::string const &sType() const;
        std::string const &name() const;

        FirstSet const &firstSet() const;

        void setReserved();
        void setStype(std::string const &stype);
        void setType(Type type);
        void used() const;       // d_used is mutable.;

    protected:
        Symbol(std::string const &name, Type t, std::string const &type = "");

    private:
        virtual FirstSet const &v_firstSet() const = 0;
};

inline std::string const &Symbol::name() const
{
    return d_name;
}

inline bool Symbol::isTerminal() const
{
    return !(d_type & NON_TERMINAL);
}

inline bool Symbol::isSymbolic() const
{
    return d_type & SYMBOLIC_TERMINAL;
}

inline bool Symbol::isNonTerminal() const
{
    return d_type & NON_TERMINAL;
}

inline bool Symbol::isUndetermined() const
{
    return d_type == UNDETERMINED;
}

inline bool Symbol::isUsed() const
{
    return d_used;
}

inline bool Symbol::isReserved() const
{
    return d_type & RESERVED;
}

inline void Symbol::setReserved()
{
    d_type |= RESERVED;
}

inline void Symbol::used() const       // d_used is mutable.
{
    d_used = true;
}

inline void Symbol::setType(Type type)
{
    d_type = type;
}

inline void Symbol::setStype(std::string const &stype)
{
    d_stype = stype;
}

inline std::string const &Symbol::sType() const
{
    return d_stype;
}

inline FirstSet const &Symbol::firstSet() const
{
    return v_firstSet();
}

// operator<< is already available through Element


#endif
