#ifndef _INCLUDED_WRITER_
#define _INCLUDED_WRITER_

#include <iosfwd>
#include <string>

#include "../next/next.h"

class Terminal;
class NonTerminal;
class Production;
class StateItem;
class State;
class Rules;

class Writer
{
    std::ostream *d_out;
    std::string const &d_baseclass;
    Rules const &d_rules;

    public:
        Writer(std::string const &baseclass, Rules const &rules);
        void useStream(std::ostream &out);

        void productions() const;
        void srTables() const;
        void statesArray() const;
        void symbolicNames() const;
        void insert(Terminal::ConstVector const &tokens) const;

    private:
        struct TokenContext
        {
            size_t lastValue;
            std::ostream &out;
        };
        static void insert(Terminal const *token, TokenContext &context);

        static void terminalSymbol(Terminal const *terminal, 
                                    std::ostream &out);
        static void nonTerminalSymbol(NonTerminal const *nonTerminal, 
                                    std::ostream &out);
        static void srTable();

        struct SRContext
        {
            std::string const &baseclassScope;
            std::ostream &out;
        };

        static void productionInfo(Production const *production, 
                                   std::ostream &out);
        static void srTable(State const *state, SRContext &sac);
        static void transitions(Next::Vector const &next, std::ostream &out);
        static void transition(Next const &next, std::ostream &out);

        static void reductions(std::ostream &out, State const &state);
        static void reduction(std::ostream &out, StateItem const &stateItem);

        struct ReductionContext
        {
            size_t ruleNr;
            std::ostream &out;
        };
        static void reduction(Element const *sym, ReductionContext &context);
};

inline Writer::Writer(std::string const &baseclass, Rules const &rules)
:
    d_out(0),
    d_baseclass(baseclass),
    d_rules(rules)
{}

inline void Writer::useStream(std::ostream &out)
{
    d_out = &out;
}

#endif
