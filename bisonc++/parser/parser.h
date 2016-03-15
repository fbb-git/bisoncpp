#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"

#include <unordered_map>

class NonTerminal;
class Terminal;
class Symbol;
class Options;
class AtDollar;

namespace FBB
{
    class Mstream;
}

#undef Parser
class Parser: public ParserBase
{
            // actions to taken given tokens returned by the lexical scanner
    typedef std::unordered_map<size_t, void (Parser::*)()>  ActionMap;
    typedef ActionMap::iterator                             Iterator;
    typedef ActionMap::value_type                           Value;

    enum SemType
    {
        SINGLE,
        UNION,
        POLYMORPHIC
    };

    enum SemTag
    {
        NONE,
        AUTO,
        EXPLICIT,
    };

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
    std::string d_field;                // %union field in <type> specs.
    bool        d_typeDirective;        // true following %type
    SemType     d_semType;              // see set{union,polymorphic}decl.cc
    bool        d_negativeDollarIndices;

    Terminal::Association d_association;

        // associations between type-identifiers and type-definitions of
        // polymorphic semantic values
    std::unordered_map<std::string, std::string> d_polymorphic;

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
    static char s_locationValue[];
                                    // name of the location value variable
                                    // used by the generated parser (@0)

    static char const s_stype__[];  // generic semantic value for POLYMORPHIC
                                    
    public:
        Parser(Rules &rules);
        int parse();
        void cleanup();             // do cleanup following parse();
        std::unordered_map<std::string, std::string> const &polymorphic() const;

    private:
        void inspectDirectives() const;
        void noConstructorChecks() const;
        void warnTagMismatches() const;

        void addPolymorphic(std::string const &tag, 
                            std::string const &typeSpec);

        void addIncludeQuotes(std::string *target); // ensure ".." or <..> 
                                                    // around target name
        void checkEmptyBlocktype();
        void checkFirstType();


        bool noID(std::string const &) const;
        bool idOK(std::string const &) const;
        bool findTag(std::string const &tag) const;

        void returnSingle(AtDollar const &atd) const;
        std::string returnUnion(AtDollar const &atd) const;
        std::string returnPolymorphic(AtDollar const &atd) const;
 
        SemTag semTag(char const *label, AtDollar const &atd, 
                     bool (Parser::*testID)(std::string const &) const) const;


        Symbol *defineNonTerminal(std::string const &name, 
                                  std::string const &stype);
        void definePathname(std::string *target);
        void defineTerminal(std::string const &name, Symbol::Type type);
        void defineTokenName(std::string const &name, bool hasValue);
        void expectRules();

        void setExpectedConflicts();
        void setLocationDecl();
        void setNegativeDollarIndices();
        void setPrecedence(int type);
        void setUnionDecl();
                                        

        size_t extractIndex(int *idx, size_t pos);
        size_t extractType(std::string *type, size_t pos, Block &block);

                                        // handles a location-value stack
                                        // reference (@) in a received action 
                                        // block
        void handleAtSign(Block &block, AtDollar const &atd, int nElements);

                                        // handles a semantic-value stack
                                        // reference ($) in a received action 
                                        // block
        bool handleDollar(Block &block, AtDollar const &atd, int nElements);


        STYPE__ handleProductionElements(STYPE__ &first, 
                                         STYPE__ const &second);
        void handleProductionElement(STYPE__ &last);


        void installAction(Block &block);
        int indexToOffset(int idx, int nElements) const;

        void multiplyDefined(Symbol const *sp);

        void nestedBlock(Block &block); // define inner block as pseudo N

        std::string nextHiddenName();

            // may generate error or warning:
        void negativeIndex(AtDollar const &atd) const;

        void warnAutoOverride(AtDollar const &atd) const;
        void warnAutoIgnored(char const *typeOrField, 
                             AtDollar const &atd) const;
        void warnUntaggedValue(AtDollar const &atd) const;

        // generating emsgs:
        bool errIndexTooLarge(AtDollar const &atd, int nElements) const;
        void errNoSemantic(char const *label, AtDollar const &atd,
                                              std::string const &id) const;

        void setStart();
        void setPolymorphicDecl();

        void openRule(std::string const &ruleName);

        void predefine(Terminal const *terminal);   // Used by Parser() to 
                                                    // pre-enter into d_symtab

        NonTerminal *requireNonTerminal(std::string const &name);

        bool substituteBlock(int nElements, Block &block);

                                        // saves the default $1 value
                                        // at the beginning of a mid-rule
                                        // action block (in substituteBlock)
        void saveDollar1(Block &block, int offset);


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
        void print__();
        void exceptionHandler__(std::exception const &exc);

                                        // used in, e.g., handleDollar
                                        // to obtain # elements for
                                        // end- or mid-rule actions
        static int nComponents(int nElements);
};

inline std::unordered_map<std::string, std::string> const &Parser::polymorphic() const
{
    return d_polymorphic;
}

#endif

