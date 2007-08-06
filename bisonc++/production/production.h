#ifndef _INCLUDED_PRODUCTION_
#define _INCLUDED_PRODUCTION_

#include <vector>
#include <string>
#include <iosfwd>
#include <algorithm>

#include "../block/block.h"
#include "../symbol/symbol.h"
#include "../terminal/terminal.h"

#include <iostream>

// NOTE: To obtain all productions of a certain Non-Terminal, use
//       NonTerminal's `productions()' member

class Production: public std::vector<Symbol *>
{
    friend std::ostream &operator<<(std::ostream &out, 
                                               Production const *production);
    private:
        Terminal const *d_precedence;
        Block           d_action;
        Symbol const *d_nonTerminal;
        size_t d_nr;                          // production order number
                                              // over all productions,
                                              // starts at 1
        mutable bool d_used;

        static size_t s_nr;
        static bool s_unused;
        static Production const *s_startProduction;
    
        static std::ostream &(Production::*s_insert[])(
                                                std::ostream &out) const;
    public:
        typedef std::vector<Production *>       Vector;
        typedef std::vector<Production const*>  ConstVector;
        typedef ConstVector::const_iterator     ConstIter;

        Production(Symbol const *nonTerminal);

        Block const &action() const;
        Symbol const &operator[](size_t idx) const;
        Symbol const *rhs(size_t idx) const;    // idx-ed symbol in the rhs
        Symbol const *lhs() const;
        Terminal const *precedence() const;
        bool hasAction() const;
        bool isEmpty() const;
        size_t nr() const;
        void used() const;  // d_used is mutable

        void setAction(Block const &block);
        void setPrecedence(Terminal const *terminal);

        static Production const *start();

        struct IAContext                    // insertActionContext
        {
            std::ostream &out;
            char const *infile;
            bool lineDirectives;
            size_t indent;
        };
        static void insertAction(Production const *prod, IAContext &context);

        static void setStart(Production const *production);

        struct TermToNontermContext
        {
            Symbol *terminal;
            Symbol *nonTerminal;
        };
        static void termToNonterm(Production *pPtr, 
                                  TermToNontermContext &t2n);

        static void unused(Production const *production);
        static bool notUsed();
        static bool isTerminal();

    private:
        Symbol *vectorIdx(size_t idx) const;
        std::ostream &standard(std::ostream &out) const;
};

inline bool Production::notUsed()
{
    return s_unused;
}

inline Symbol const *Production::rhs(size_t idx) const
{
    return vectorIdx(idx);
}

inline Symbol const *Production::lhs() const
{
    return d_nonTerminal;
}

inline size_t Production::nr() const
{
    return d_nr;
}

inline void Production::used() const
{
    d_used = true;
}

inline Block const &Production::action() const
{
    return d_action;
}

inline bool Production::hasAction() const
{
    return !d_action.empty();
}

inline bool Production::isEmpty() const
{
    return empty() && d_action.empty();
}

inline Terminal const *Production::precedence() const
{
    return d_precedence;
}

inline Symbol const &Production::operator[](size_t idx) const
{
    return *vectorIdx(idx);
}

inline void Production::setAction(Block const &block)
{
    d_action = block;
}
 
inline void Production::setStart(Production const *production)
{
    s_startProduction = production;
}

inline Production const *Production::start()
{
    return s_startProduction;
}

inline std::ostream &operator<<(std::ostream &out, Production const *prod)
{
    return prod->standard(out);
}

inline bool isTerminal(Symbol const *symbol)
{
    return symbol->isTerminal();
}

inline void Production::termToNonterm(Production *pPtr, 
                                      TermToNontermContext &t2n)
{
    std::replace(pPtr->begin(), pPtr->end(), t2n.terminal, t2n.nonTerminal);
}

#endif

