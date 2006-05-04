#ifndef _INCLUDED_GENERATOR_
#define _INCLUDED_GENERATOR_

#include <vector>
#include <map>
#include <string>
#include <iosfwd>

class Terminal;
class NonTerminal;
class Parser;
class Rules;
class ItemSets;

class Generator
{
    Rules const &d_rules;
    Parser const &d_parser;

    std::string d_baseclassScope;
    std::string const &d_nameSpace;

    mutable std::string d_key;          // extracted at $insert statements
    mutable unsigned d_indent;

    typedef std::map<std::string, void (Generator::*)(std::ostream &) const>
            MapInsert;
    typedef MapInsert::value_type
            MapInsertValue;
    typedef MapInsert::const_iterator
            MapInsertConstIter;

    struct SSContext                        // selectSymbolicContext
    {
        std::vector<Terminal const *> *symbolicTokens;
    };

    struct TContext                         // terminalContext
    {
        std::ostream &out;
    };

    static MapInsertValue s_mapValues[];
    static MapInsert s_insert;

    mutable std::string d_line;
    bool        d_debug;
    
    public:
        Generator(Rules const &rules, Parser const &parser);

        void baseclassHeader() const;
        void classHeader() const;
        void implementationHeader() const;
        void parseFunction() const;
        void parsingTable() const;

    private:
        void filter(std::istream &in, std::ostream &out) const;
        void insert(std::ostream &out) const;
        void key(std::ostream &out) const;

        void actionCases(std::ostream &out) const;
        void baseClass(std::ostream &out) const;
        void classH(std::ostream &out) const;
        void classIH(std::ostream &out) const;
        void debug(std::ostream &out) const;
        void debugIncludes(std::ostream &out) const;
        void debugFunctions(std::ostream &out) const;
        void debugInit(std::ostream &out) const;
        void debugDecl(std::ostream &out) const;
        void lex(std::ostream &out) const;
        void ltype(std::ostream &out) const;
        void ltypeData(std::ostream &out) const;
        void ltypePop(std::ostream &out) const;
        void ltypePush(std::ostream &out) const;
        void ltypeResize(std::ostream &out) const;
        void ltypeStack(std::ostream &out) const;
        void namespaceClose(std::ostream &out) const;
        void namespaceOpen(std::ostream &out) const;
        void namespaceUse(std::ostream &out) const;
        void preIncludes(std::ostream &out) const;
        void scannerH(std::ostream &out) const;
        void scannerObject(std::ostream &out) const;
        void staticData(std::ostream &out) const;
        void stype(std::ostream &out) const;
        void tokens(std::ostream &out) const;

        void productionInfo(std::ostream &out) const;
        void srTables(std::ostream &out) const;
        void stateArray(std::ostream &out) const;
        void symbolData(std::ostream &out) const;

        static void selectSymbolic(Terminal const *terminal, 
                            SSContext &context);

        static void nonTerminal(NonTerminal const *nonTerminal, 
                                TContext &context);

        static void terminal(Terminal const *terminal, 
                             TContext &context);
};

        
#endif
