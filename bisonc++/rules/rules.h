#ifndef _INCLUDED_RULES_
#define _INCLUDED_RULES_

#include <iostream>

#include <vector>
#include <set>
#include <string>
#include <algorithm>
#include <unordered_map>

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
    bool d_defaultAction;       // last action was default action:
                                // requires line update at the next
                                // rule definition
    public:
            // For each rule, maintain a record of file/line combinations
            // indicating where the rule was first seen. This allows me to
            // generate warnings when a rule is defined as full rule
            // definitions rather than as alternatives. There's nothing
            // inherently wrong with that, but it may also be a typo causing
            // unexpected conflicts
        typedef std::pair<std::string, size_t> FileInfo;

        //FBB: 20160412 - see also sethiddenaction.cc for the use
        //                of the 90000 line number flag that was used to flag
        //                a hidden action. Apparently it was nowhere used
        //                so I decided not to use it anymore.

    private:
        typedef std::unordered_map<NonTerminal const *, FileInfo> 
                                                            NFileInfoMap;
    
        Terminal::Vector d_terminal;        // the vector holding information 
                                            // about defined terminal symbols

        NonTerminal::Vector d_nonTerminal;  // the vector holding information  
                                            // about defined nonterminals
    
        NFileInfoMap d_location;            // the map holding information
                                            // about initial rule locations

        NonTerminal *d_currentRule;         // Pointer to the N currently
                                            // processed. Initially 0
    
        std::string d_startRule;            // name of the startrule
    
        Production::Vector d_production;    // the vector holding information
                                            // about all productions
                                            // productions hold Symbol
                                            // elements, they contain
                                            // information about type and
                                            // index of their elements in the 
                                            // (non)terminal vectors

        Production *d_currentProduction;    // currently processed production
                                            // rule (pointer to a Production
                                            // also in d_production)
    
        static size_t s_acceptProductionNr; // index in d_production of the
                                            // accept rule

        static size_t s_nExpectedConflicts; // how many conflicts to expect?
        static Terminal s_errorTerminal;    // predefined 'error' terminal
        static Terminal s_eofTerminal;      // predefined eof terminal
        static Symbol *s_startSymbol;       // derived from the initial N or
                                            // from the N defined as the
                                            // star tsymbol by
                                            // augmentGrammar().

        static size_t s_lastLineNr;         // last received line nr, used by
                                            // setHiddenAction()
    
    public:
        Rules();

        static void setExpectedConflicts(size_t value);
        static Terminal const *eofTerminal();
        static Terminal const *errorTerminal();
        static size_t acceptProductionNr();
        static size_t expectedConflicts();

        void clearLocations();                  // clear d_location

        Terminal *insert(Terminal *terminal, std::string const &literal);
        NonTerminal *insert(NonTerminal *nonTerminal);

        void addElement(Symbol *symbol);
                // add the symbol as the next element of the 
                // rule-production that's currently being defined. 

        void updateDefaultActionLineNr(size_t lineNr);
        void addProduction(size_t lineNr);
                // add a new production to the set of productions of the
                // rule currently being defined

        bool newRule(NonTerminal *nonTerminal, std::string const &source,
                                                size_t lineNr);
                // add a new rule. If startrule has not
                // yet been set, define this rule as the startrule.
                // return true if a really new rule was added, rather than
                // expanding a rule defined earlier.

        void assignNonTerminalNumbers();
        void augmentGrammar(Symbol *start);

        Production const &lastProduction() const;

        FileInfo const &fileInfo(NonTerminal const *nt) const;
                                            // return the FileInfo of the
                                            // first definition of rule `nt'

        std::string const &name() const;    // return the name of the 
                                            // currently defined rule

        std::string const &sType() const;   // return the value type
                                            // associated with the 
                                            // currently defined rule.

        std::string const &sType(size_t idx) const; // return the value type
                                        // associated with element idx of
                                        // the currently defined production

        Symbol const *symbol(size_t idx) const; 
                                        // return the symbol
                                        // associated with element idx of
                                        // the currently defined production
                                        // Note: symbol idx MUST exist

        size_t nProductions() const;

        size_t nElements() const;

        void determineFirst();

        bool hasRules() const;

                // associate an action with the currently defined rule
                // production 
        void setAction(Block const &block, bool defaultAction = false);

        void setHiddenAction(Block const &block);

        void setLastTerminalValue(size_t value);

        void setLastPrecedence(size_t value);

        void updatePrecedences();       // try to assign a precedence to 
                                        // productions that don't yet have a
                                        // precedence associated to them

        void setPrecedence(Terminal const *terminal);
                // Set the explicit precedence of the currently defined
                // production to the precedence of the given terminal.

        void showFirst() const;         // show the First-sets

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
        void termToNonterm(Symbol *term, Symbol *nonTerm);

    private:
        static bool isTerminal(Symbol const *symbol);
        static void updatePrecedence(Production *production, 
                                     Terminal::Vector const &tv);
};

inline Rules::Rules()
:
    d_currentRule(0),
    d_currentProduction(0)
{}                        
                          
inline void Rules::clearLocations()
{
    d_location.clear();
}

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

inline void Rules::setAction(Block const &block, bool defaultAction)
{
    d_defaultAction = defaultAction;
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

inline Rules::FileInfo const &Rules::fileInfo(NonTerminal const *nt) const
{
    return d_location.find(nt)->second;
}

inline Symbol const *Rules::symbol(size_t idx) const
{
    return d_currentProduction->rhs(idx - 1);
}
        
#endif

