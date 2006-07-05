#ifndef _INCLUDED_TERMINAL_
#define _INCLUDED_TERMINAL_

#include <string>
#include <vector>
#include <set>

#include "../symbol/symbol.h"

class Terminal: public Symbol
{
    public:
        enum
        {
            INITIAL_SYMBOLIC_VALUE = 257,   // See rules/data.cc for Terminals
                                            // defined by default.
            DEFAULT = UINT_MAX      // results in the next symbolic terminal
                                    // value to be assigned.
        };
        enum Association        // adapt s_association[] in data.cc if this
        {                       // changes
            UNDEFINED,
            NONASSOC,
            LEFT,
            RIGHT,
        };
        enum PriorityComparison
        {
            SMALLER = -1,
            EQUAL   = 0,
            LARGER  = 1,
        };

    private:
        static std::set<unsigned> s_valueSet;   // all terminal token values
        static unsigned s_priority;
        static char const *s_association[];
        static unsigned s_value;        // value assigned, unless explictly
                                        // requested
        static unsigned s_maxValue;     // maximum assigned terminal value

        unsigned d_value;
        Association d_association;
        unsigned d_priority;

        std::string d_literal;
        std::string d_readableLiteral;

        FirstSet d_firstSet;
    public:
        static Terminal *downcast(Symbol *sp)
        {
            return dynamic_cast<Terminal *>(sp);
        }

        static Terminal const *downcast(Element const *sp)
        {
            return dynamic_cast<Terminal const *>(sp);
        }

        static bool compareValues(Terminal const *left, Terminal const *right)
        {
            return left->d_value < right->d_value;
        }

        static PriorityComparison comparePriorities(Terminal const *first,
                                                    Terminal const *second);

        static void incrementPriority()
        {
            ++s_priority;
        }
        static void resetPriority()     // see Parser::parseDeclarations()
        {
            s_priority = 0;
        }

        static bool setUnique(unsigned value);    // true if unique
        static void unused(Terminal const *terminal);
        static unsigned maxValue()
        {
            return s_maxValue;
        }

        Terminal(std::string const &name, 
                    Type type,
                    unsigned value = DEFAULT, 
                    Association association = UNDEFINED, 
                    std::string const &stype = ""); // stype: type assigned by 
                                    // explicit symbol type association, 
                                    // e.g. %type <int> symbol

        Terminal(std::string const &name,       // used for reserved terminals
                std::string const &literal,
                    Type type);


        virtual ~Terminal();

        std::string const &literal() const
        {
            return d_literal;
        }
        Association association() const
        {
            return d_association;
        }
        PriorityComparison comparePriority(Terminal const *other) const
        {
            return 
                d_priority > other->d_priority ? LARGER  :
                d_priority < other->d_priority ? SMALLER :
                                                 EQUAL;
        }            
        unsigned priority() const
        {
            return d_priority;
        }
        unsigned value() const
        {
            return d_value;
        }

        virtual FirstSet const &firstSet() const
        {
            return d_firstSet;
        }        

        void setLiteral(std::string const &literal)
        {
            d_literal = literal;
        }
        void setValue(unsigned value);  // reassign a token value
        void setPriority(unsigned value)
        {
            d_priority = value;
        }
        static void showSymbolic(Terminal const *term);

        virtual std::string const &display() const
        {
            return d_readableLiteral;
        }
};

#endif



