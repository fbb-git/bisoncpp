#ifndef _INCLUDED_RULES_
#define _INCLUDED_RULES_

#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>

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
    Terminal::Vector d_terminal;        // the vector holding information 
                                        // about defined terminal symbols

    NonTerminal::Vector d_nonTerminal; 
                                            // the vector holding information 
    NonTerminal *d_currentRule;             // about defined nonterminals

    std::string d_startRule;                // name of the startrule

    Production::Vector d_production;        // the vector holding information
    Production *d_currentProduction;        // about all productions
                                            // productions hold Symbol
                                            // elements, they contain
                                            // information about type and
                                            // index of their elements in the 
                                            // (non)terminal vectors

    static size_t s_acceptProductionNr;
    static size_t s_nExpectedConflicts;
    static Terminal s_errorTerminal;
    static Terminal s_eofTerminal;
    static Symbol *s_startSymbol;

    public:
        Rules();

        static void setExpectedConflicts(size_t value);
        static Terminal const *eofTerminal();
        static Terminal const *errorTerminal();
        static size_t acceptProductionNr();
        static size_t expectedConflicts();


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

        Production const &lastProduction() const;

        std::string const &name() const;    // return the name of the 
                                            // currently defined rule

        std::string const &sType() const;   // return the value type
                                            // associated with the 
                                            // currently defined rule.

        std::string const &sType(size_t idx) const; // return the value type
                                        // associated with element idx of
                                        // the currently defined production

        size_t nProductions() const;

        size_t nElements() const;

        void determineFirst();
        void determineFollow();

        bool hasRules() const;

                // associate an action with the currently defined rule
                // production 
        void setAction(Block const &block);

        void setHiddenAction(Block const &block);

        void setLastTerminalValue(size_t value);

        void setLastPrecedence(size_t value);

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
        void showUnusedRules() const;

        void setStartRule(std::string const &start);
        std::string const &startRule() const;

        Production const *startProduction();

        static Symbol const *startSymbol() ;

        std::vector<NonTerminal const *> const &nonTerminals() const;
        std::vector<Terminal const *> const &terminals() const;
        std::vector<Production const *> const &productions() const;
        void setNonTerminalTypes();

    private:
        static void addFollowFromFirst(Production *production);
        
            // called by determineFollow() to process each NonTerminal
            // It will in turn process each of the nonterminal's productions
        static void addFirstToFollow(NonTerminal *nonTerminal);

        void addFollowToFollow();
        static void expandFollow(Production *production);
};


inline Rules::Rules()
:
    d_currentRule(0),
    d_currentProduction(0)
{}

inline void Rules::setExpectedConflicts(size_t value)
{
    s_nExpectedConflicts = value;
}

inline Terminal const *Rules::eofTerminal()
{
    return &s_eofTerminal;
}

inline Terminal const *Rules::errorTerminal()
{
    return &s_errorTerminal;
}

inline size_t Rules::acceptProductionNr()
{
    return s_acceptProductionNr;
}

inline size_t Rules::expectedConflicts()
{
    return s_nExpectedConflicts;
}

inline Production const &Rules::lastProduction() const
{
    return *d_currentProduction;
}

inline std::string const &Rules::name() const
{
    return d_currentRule->name();
}

inline std::string const &Rules::sType() const  
{                                 
                                  
    return d_currentRule->sType(); 
}

inline size_t Rules::nProductions() const
{
    return d_currentRule->nProductions();
}

inline bool Rules::hasRules() const
{
    return d_currentRule;
}

inline size_t Rules::nElements() const
{
    return d_currentProduction->size();
}

inline void Rules::setAction(Block const &block)
{
    d_currentProduction->setAction(block);
}

inline void Rules::setLastTerminalValue(size_t value)
{
    d_terminal.back()->setValue(value);
}

inline void Rules::setLastPrecedence(size_t value)
{
    d_terminal.back()->setPrecedence(value);
}

inline void Rules::setStartRule(std::string const &start)
{
    d_startRule = start;
}

inline std::string const &Rules::startRule() const
{
    return d_startRule;
}

inline Production const *Rules::startProduction()
{
    return d_currentProduction;
}

inline Symbol const *Rules::startSymbol() 
{
    return s_startSymbol;
}

inline std::vector<NonTerminal const *> const &Rules::nonTerminals() const
{
    void const *vp = &d_nonTerminal;
    return *reinterpret_cast<std::vector<NonTerminal const *> const *>
           (vp);
}

inline std::vector<Terminal const *> const &Rules::terminals() const
{
    void const *vp = &d_terminal;
    return 
        *reinterpret_cast<std::vector<Terminal const *> const *>(vp);
}

inline std::vector<Production const *> const &Rules::productions() const
{
    void const *vp = &d_production;
    return *reinterpret_cast<std::vector<Production const *> const *>
           (vp);
}

inline void Rules::addFirstToFollow(NonTerminal *nonTerminal)
{
    for_each(nonTerminal->productions().begin(), 
             nonTerminal->productions().end(), 
            &addFollowFromFirst);
}
        
#endif

