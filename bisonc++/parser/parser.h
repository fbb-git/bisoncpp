#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"

class NonTerminal;
class Terminal;
class Symbol;
class Options;

namespace FBB
{
    class Mstream;
}

#undef Parser
class Parser: public ParserBase
{
            // actions to taken given tokens returned by the lexical scanner
    typedef std::map<size_t, void (Parser::*)()> 
            ActionMap;
    typedef ActionMap::iterator 
            Iterator;
    typedef ActionMap::value_type 
            Value;

            // data members that are self-explanatory are not explicitly
            // described here.

    FBB::Arg &d_arg;
    Options &d_options;

    // $insert scannerobject
    Scanner d_scanner;
    std::string const &d_matched;

    Rules      &d_rules;
    Symtab      d_symtab;

    std::string d_expect;
    std::string d_field;                    // %union field in <type> specs.
    bool        d_typeDirective;            // true following %type
    bool        d_unionDeclared;            // see setuniondecl.cc
    bool        d_negativeDollarIndices;

    Terminal::Association d_association;

                                // used in processBlock() and sipIgnore()
    std::vector<Block::Range>::const_reverse_iterator d_skipRbegin;
    std::vector<Block::Range>::const_reverse_iterator d_skipRend;

    static size_t s_nHidden;          // number of hidden nonterminals
    static std::ostringstream s_hiddenName;

    static char s_semanticValue[];  // name of the semantic value variable
                                    // used by the generated parser
    static char s_semanticValueStack[];  
                                    // name of the semantic value stack
                                    // used by the generated parser
    static char s_locationValueStack[];  
                                    // name of the location value stack
                                    // used by the generated parser

    public:
        Parser(Rules &rules);
        int parse();
        void cleanup();             // do cleanup following parse();

    private:
        void addIncludeQuotes(std::string *target); // ensure ".." or <..> 
                                                    // around target name
        void checkEmptyBlocktype();
        void checkFirstType();

        bool defaultReturn(size_t pos, Block &block);
        Symbol *defineNonTerminal(std::string const &name, 
                                  std::string const &stype);
        void definePathname(std::string *target);
        void defineTerminal(std::string const &name, Symbol::Type type);
        void defineTokenName(std::string *name, bool hasValue);
        void expectRules();

        void setExpectedConflicts();
        void setLocationDecl();
        void setNegativeDollarIndices();
        void setPrecedence(int type);
        void setUnionDecl();
                                        

        bool explicitElement(size_t pos, int nElements, Block &block);
        bool explicitReturn(size_t pos, Block &block);
        size_t extractIndex(int *idx, size_t pos);
        size_t extractType(std::string *type, size_t pos, Block &block);

        void handleAtSign(size_t idx, int nElements, Block &block);
                                        // handle a location-value stack
                                        // reference (@) in a received action 
                                        // block
        bool handleDollar(size_t idx, int nElements, Block &block);
                                        // handle a semantic-value stack
                                        // reference ($) in a received action 
                                        // block

        FBB::PTag *handleProductionElements(FBB::PTag *first, 
                                            FBB::PTag *second);
        void handleProductionElement(FBB::PTag *last);


        void installAction(Block &block);
        int indexToOffset(int idx, int nElements) const;

        void multiplyDefined(Symbol const *sp);

        void nestedBlock(Block &block); // define inner block as pseudo N

        std::string nextHiddenName();
        void noDefaultTypeWarning();

        void setStart();

        bool numberedElement(size_t pos, int nElements, Block &block);

        void openRule(std::string *ruleNamePtr);

        void predefine(Terminal const *terminal);   // Used by Parser() to 
                                                    // pre-enter into d_symtab

        NonTerminal *requireNonTerminal(std::string const &name);

        size_t skipIgnore(size_t pos);
        bool substituteBlock(int nElements, Block &block);

        Symbol *useSymbol();
        Terminal *useTerminal();

        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
                                        // used in, e.g., explicitElement()
                                        // to obtain # elements for
                                        // end- or mid-rule actions
        static size_t nComponents(int nElements);
};

// $insert lex
inline int Parser::lex()
{
    return d_scanner.lex();
}

inline void Parser::print()
{}


inline void Parser::setNegativeDollarIndices()
{
    d_negativeDollarIndices = true;
}        


//inline std::ostream &Parser::lineMsg(FBB::Mstream &mstream)
//{
//    return d_scanner.lineMsg(mstream);
//}


inline void Parser::setExpectedConflicts()
{
    Rules::setExpectedConflicts(d_scanner.number());
}


//inline std::string *Parser::newYYText() const
//{
//    return new std::string(d_scanner.YYText());
//}

inline size_t Parser::nComponents(int nElements)
{
    return nElements >= 0 ? nElements : -nElements - 1;
}

#endif

