#ifndef _INCLUDED_NONTERMINAL_
#define _INCLUDED_NONTERMINAL_

#include <vector>
#include <string>

#include "../symbol/symbol.h"
#include "../production/production.h"
#include "../firstset/firstset.h"
#include "../followset/followset.h"

class NonTerminal: public Symbol
{
    public:
        typedef std::vector<Production *>
                ProdVect;
        typedef ProdVect::const_iterator 
                ProdConstIter;
        typedef ProdVect::iterator 
                ProdIter;

    private:
        ProdVect d_production;  // production rules in a vector
                                // of ptrs to Production objects
        FirstSet    d_first;
        FollowSet   d_follow;

        unsigned d_nr;          // the NonTerminal's number

        static unsigned s_counter;
        static unsigned s_number;   // incremented at each call of setNr()
        
    public:
        static void setFirstNr(unsigned nr)
        {
            s_number = nr;
        }
        static void setNr(NonTerminal *np)
        {
            np->d_nr = s_number++;
        }
        static unsigned counter() 
        {
            return s_counter;
        }
        static void countFollow(NonTerminal *nonTerminal)
        {
            s_counter += nonTerminal->d_follow.setSize();
        }
        static void resetCounter()
        {
            s_counter = 0;
        }
        static void setFirst(NonTerminal *nonTerminal);
        static void showFollow(NonTerminal const *nonTerminal);
        static void showFirst(NonTerminal const *nonTerminal);
        static void setNonTerminal(NonTerminal *nonTerminal)
        {
            nonTerminal->setType(NON_TERMINAL);
        }
        static void undefined(NonTerminal const *nonTerminal);
        static void unused(NonTerminal const *nonTerminal);

        NonTerminal(std::string const &name, std::string const &stype = "",
                                Type type = NON_TERMINAL);
        ~NonTerminal();

        
        unsigned firstSize() const
        {
            return d_first.setSize();
        }

        std::set<Element const *> const &firstTerminals() const
        {
            return d_first;
        }

        virtual FirstSet const &firstSet() const
        {
            return d_first;
        }

        void addProduction(Production *next)
        {
            d_production.push_back(next);
        }

        unsigned nProductions() const
        {
            return d_production.size();
        }

        unsigned nr() const
        {
            return d_nr;
        }

        void addEpsilon() 
        {
            d_first.addEpsilon();
        }

        void setEOFinFollow()
        {
            d_follow.setEOF();
        }

        ProdVect &productions()
        {
            return d_production;
        }
        
        ProdVect const &productions() const
        {
            return d_production;
        }
        
        static NonTerminal *downcast(Symbol *sp)
        {
            return dynamic_cast<NonTerminal *>(sp);
        }

        static NonTerminal const *downcast(Symbol const *sp)
        {
            return dynamic_cast<NonTerminal const *>(sp);
        }

        void addToFollow(FirstSet const &firstSet)
        {
            d_follow += firstSet;
        }

        void addToFollow(NonTerminal const *nonTerminal)
        {
            d_follow += nonTerminal->d_follow;
        }

    private:
        static void showName(std::string const &name);
};

        
#endif

