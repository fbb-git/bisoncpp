#ifndef _INCLUDED_NONTERMINAL_
#define _INCLUDED_NONTERMINAL_

#include <iomanip>

#include <vector>
#include <string>

#include "../symbol/symbol.h"
#include "../production/production.h"
#include "../firstset/firstset.h"

class NonTerminal: public Symbol
{
    public:
        typedef std::vector<NonTerminal *> Vector;

    private:
        Production::Vector d_production;  // production rules in a vector
                                    // of ptrs to Production objects

        FirstSet    d_first;        // set of terminals that can be
                                    // encountered at this NonTerminal

        size_t d_nr;                // the NonTerminal's number

        static size_t s_counter;    // counts the number of symbols in first
                                    // sets. May be reset to 0 by
                                    // resetCounter()
        static size_t s_number;     // incremented at each call of setNr()
        static bool s_unused;       // prevents multiple unused warnings
        static bool s_undefined;    // set to true once at least one
                                    // nonterminal is not used.
        
        static std::ostream &(NonTerminal::*s_insertPtr)(std::ostream &out)
                                                                        const;
                                    // pointer to the insertion function to be
                                    // used. 
    public:
        NonTerminal(std::string const &name, std::string const &stype = "",
                                Type type = NON_TERMINAL);
        ~NonTerminal();

        Production::Vector &productions();
        Production::Vector const &productions() const;
        size_t firstSize() const;
        size_t nProductions() const;
        std::set<Element const *> const &firstTerminals() const;
        void addEpsilon() ;
        void addProduction(Production *next);

        static NonTerminal *downcast(Symbol *sp);
        static NonTerminal const *downcast(Symbol const *sp);
        static size_t counter();
        static void resetCounter();
        static void setFirst(NonTerminal *nonTerminal);
        static void setFirstNr(size_t nr);
        static void setNonTerminal(NonTerminal *nonTerminal);
        static void setNr(NonTerminal *np);
        static void undefined(NonTerminal const *nonTerminal);
        static void unused(NonTerminal const *nonTerminal);
        static bool notUsed();
        static bool notDefined();

        static void inserter(std::ostream &(NonTerminal::*insertPtr)
                                        (std::ostream &out) const);

                                        // plain name
        std::ostream &plainName(std::ostream &out) const;
        std::ostream &nameAndFirstset(std::ostream &out) const;

                                    // the N's value 
        std::ostream &value(std::ostream &out) const;
        using Symbol::value;

    private:
        virtual std::ostream &insert(std::ostream &out) const;
        virtual size_t v_value() const;
        virtual FirstSet const &v_firstSet() const;

        std::ostream &insName(std::ostream &out) const;
};

inline bool NonTerminal::notUsed()
{
    return s_unused;
}

inline bool NonTerminal::notDefined()
{
    return s_undefined;
}

inline std::ostream &NonTerminal::plainName(std::ostream &out) const
{
    return out << name();
}

inline std::ostream &NonTerminal::nameAndFirstset(std::ostream &out) const
{
    return insName(out) << d_first;
}

inline std::ostream &NonTerminal::value(std::ostream &out) const
{
    return out << std::setw(3) << v_value();
}


inline void NonTerminal::setFirstNr(size_t nr)
{
    s_number = nr;
}

inline void NonTerminal::setNr(NonTerminal *np)
{
    np->d_nr = s_number++;
}

inline size_t NonTerminal::counter() 
{
    return s_counter;
}

inline void NonTerminal::resetCounter()
{
    s_counter = 0;
}

inline void NonTerminal::setNonTerminal(NonTerminal *nonTerminal)
{
    nonTerminal->setType(NON_TERMINAL);
}

inline size_t NonTerminal::firstSize() const
{
    return d_first.setSize();
}

inline std::set<Element const *> const &NonTerminal::firstTerminals() const
{
    return d_first.set();
}

inline void NonTerminal::addProduction(Production *next)
{
    d_production.push_back(next);
}

inline size_t NonTerminal::nProductions() const
{
    return d_production.size();
}

inline void NonTerminal::addEpsilon() 
{
    d_first.addEpsilon();
}

inline Production::Vector &NonTerminal::productions()
{
    return d_production;
}

inline Production::Vector const &NonTerminal::productions() const
{
    return d_production;
}

inline NonTerminal *NonTerminal::downcast(Symbol *sp)
{
    return dynamic_cast<NonTerminal *>(sp);
}

inline NonTerminal const *NonTerminal::downcast(Symbol const *sp)
{
    return dynamic_cast<NonTerminal const *>(sp);
}

inline void NonTerminal::inserter(std::ostream &(NonTerminal::*insertPtr)
                                           (std::ostream &out) const)
{
    s_insertPtr = insertPtr;
}

// operator<< is already available through Element

#endif

