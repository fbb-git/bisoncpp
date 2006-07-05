#ifndef _INCLUDED_RULES_
#define _INCLUDED_RULES_

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>

#include "../block/block.h"
#include "../terminal/terminal.h"
#include "../nonterminal/nonterminal.h"
#include "../production/production.h"
#include "../symbol/symbol.h"

    // A Rule contains the information about a rule. 
    // Its number, and a vector of Alternatives. an Alternative is a vector of
    // iterators into the symbol table
class Rules
{
    static unsigned s_acceptProductionNr;
    static unsigned s_nExpectedConflicts;
    static Terminal s_errorTerminal;
    static Terminal s_eofTerminal;
    static Symbol *s_startSymbol;

    std::vector<Terminal *> d_terminal;  // the vector holding information 
                                        // about defined terminal symbols

    std::vector<NonTerminal *> d_nonTerminal; 
                                            // the vector holding information 
    NonTerminal *d_currentRule;             // about defined nonterminals

    std::string d_startRule;                // name of the startrule

    std::vector<Production *> d_production; // the vector holding information
    Production *d_currentProduction;        // about all productions
                                            // productions hold Symbol
                                            // elements, they contain
                                            // information about type and
                                            // index of their elements in the 
                                            // (non)terminal vectors

    std::ofstream d_verbose;

    public:
        std::streambuf *infoToVerbose() const;

        static void setExpectedConflicts(unsigned value)
        {
            s_nExpectedConflicts = value;
        }
        static Terminal const *eofTerminal()
        {
            return &s_eofTerminal;
        }
        static Terminal const *errorTerminal()
        {
            return &s_errorTerminal;
        }
        static unsigned acceptProductionNr()
        {
            return s_acceptProductionNr;
        }
        static unsigned expectedConflicts()
        {
            return s_nExpectedConflicts;
        }


        Terminal *insert(Terminal *terminal, std::string const &literal);
        NonTerminal *insert(NonTerminal *nonTerminal);
        void remove(NonTerminal *nonTerminal);  // nonTerminal MUST be 
                                                // present (see, e.g.,
                                                // parser/defineterminal.cc)


        void addElement(Symbol *symbol);
                // add the symbol as the next element of the 
                // rule-production that's currently being defined. 

        void addProduction();
                // add a new production to the set of productions of the
                // rule currently being defined

        void addRule(NonTerminal *nonTerminal);
                // add a new rule. If startrule has not
                // yet been set, define this rule as the startrule.

        void assignNonTerminalNumbers();
        void augmentGrammar(Symbol *start);

        Production const &lastProduction() const
        {
            return *d_currentProduction;
        }

        std::string const &name() const  // return the name of the 
        {                                           // currently defined rule
            return d_currentRule->name();
        }

        std::streambuf *setVerbose(std::string const &filename);

        std::string const &sType() const  // return the value type
        {                                           // associated with the 
                                                    // currently defined rule.
            return d_currentRule->sType(); 
        }

        std::string const &sType(unsigned idx) const; // return the value type
                                        // associated with element idx of
                                        // the currently defined production

        unsigned nProductions() const
        {
            return d_currentRule->nProductions();
        }

        unsigned nElements() const
        {
            return d_currentProduction->size();
        }

        void determineFirst();
        void determineFollow();

                // associate an action with the currently defined rule
                // production 
        void setAction(Block const &block)
        {
            d_currentProduction->setAction(block);
        }

        void setHiddenAction(Block const &block);

        void setLastTerminalValue(unsigned value)
        {
            d_terminal.back()->setValue(value);
        }

        void setLastPriority(unsigned value)
        {
            d_terminal.back()->setPriority(value);
        }

        void setPrecedence(Terminal const *terminal);
                // Set the explicit precedence of the currently defined
                // production to the precedence of the given terminal.

        void showFirst() const;         // show the First-sets
        void showFollow() const;        // show the Follow-sets

        void showTerminals() const;     // show symbolic terminals and their
                                        // values

        void showRules() const;         // show the rule/productions

        void showUnusedTerminals() const;
        void showUnusedNonTerminals() const;

        void setStartRule(std::string const &start)
        {
            d_startRule = start;
        }
        std::string const &startRule() const
        {
            return d_startRule;
        }

        Production *startProduction()
        {
            return d_currentProduction;
        }

        static Symbol const *startSymbol() 
        {
            return s_startSymbol;
        }

        std::vector<NonTerminal const *> const &nonTerminals() const
        {
            void const *vp = &d_nonTerminal;
            return *reinterpret_cast<std::vector<NonTerminal const *> const *>
                   (vp);
        }
        std::vector<Terminal const *> const &terminals() const
        {
            void const *vp = &d_terminal;
            return 
                *reinterpret_cast<std::vector<Terminal const *> const *>(vp);
        }
        std::vector<Production const *> const &productions() const
        {
            void const *vp = &d_production;
            return *reinterpret_cast<std::vector<Production const *> const *>
                   (vp);
        }
        void setNonTerminalTypes();

    private:
        static void addFollowFromFirst(Production *production);
        
            // called by determineFollow() to process each NonTerminal
            // It will in turn process each of the nonterminal's productions
        static void addFirstToFollow(NonTerminal *nonTerminal)
        {
            for_each(nonTerminal->productions().begin(), 
                     nonTerminal->productions().end(), 
                    &addFollowFromFirst);
        }

        void addFollowToFollow();
        static void expandFollow(Production *production);
};
        
#endif

