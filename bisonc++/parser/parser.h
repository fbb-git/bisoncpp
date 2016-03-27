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

//FBB
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
    bool        d_typeDirective = false;// true following %type
    bool        d_negativeDollarIndicesOK = false;

    SemType     d_semType = SINGLE;     // see set{union,polymorphic}decl.cc

        // ADfun: pointer to member function handling @ and $ constructions
    typedef bool (Parser::*ADfun)
                        (int nElements, Block &block, AtDollar const &atd);

        // ADmap: unordered map returning a function given an 
        //                                              AtDollar::Pattern
    typedef std::unordered_map<int, ADfun> ADmap;

    ADmap *d_atDollar = &s_single;

    Terminal::Association d_association;

        // associations between tags (keys) and types (values) of
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
                                    
    static std::string const s_undefined;


    static ADmap s_single;
    static ADmap s_union;
    static ADmap s_polymorphic;

    public:
        Parser(Rules &rules);
        int parse();
        void cleanup();             // do cleanup following parse();
        std::unordered_map<std::string, std::string> const &polymorphic() const;

    private:
        std::ostream &stdWmsg(AtDollar const &atd) const;
        std::ostream &stdEmsg(AtDollar const &atd) const;
        void warnNegativeDollarIndices(AtDollar const &atd) const;

        int indexToOffset(int idx, int nElements) const;
        std::string checkRuleTag(AtDollar const &atd) const;
        bool checkExistingTag(AtDollar const &atd) const;
        bool errIndexTooLarge(AtDollar const &atd, int nElements) const;
        void warnForceLSP(size_t lineNr) const;
        void warnMissingSemval() const;

        void substituteBlock(int nElements, Block &block);


        bool dval(int nElements, Block &block, AtDollar const &atd);

        bool dvalDirectMem(int nElements, Block &block, AtDollar const &atd);
        bool dvalDirectPtr(int nElements, Block &block, AtDollar const &atd);

        bool dvalDirectReplace(Block &block, AtDollar const &atd, 
                                                        char const *suffix);

        bool dvalMem(int nElements, Block &block, AtDollar const &atd);
        bool dvalPtr(int nElements, Block &block, AtDollar const &atd);
        bool dvalRef(int nElements, Block &block, AtDollar const &atd);

        bool dvalReplace(Block &block, AtDollar const &atd, 
                                                    char const *suffix);

        bool errNegative(int nElements, Block &block, AtDollar const &atd);
        bool errNoRef(int nElements, Block &block, AtDollar const &atd);
        bool errNoTag(int nElements, Block &block, AtDollar const &atd);

        bool loc(int nElements, Block &block, AtDollar const &atd);
        bool locEl(int nElements, Block &block, AtDollar const &atd);

        std::string svsElement(int nElements, AtDollar const &ard) const;

        bool svs(int nElements, Block &block, AtDollar const &atd);

        bool svsDirectMem(int nElements, Block &block, AtDollar const &atd);
        bool svsDirectPtr(int nElements, Block &block, AtDollar const &atd);
        bool svsDirectReplace(int nElements, Block &block, 
                              AtDollar const &atd, char const *suffix);

        bool svsMem(int nElements, Block &block, AtDollar const &atd);

        bool svsPtr(int nElements, Block &block, AtDollar const &atd);
        bool svsRef(int nElements, Block &block, AtDollar const &atd);

        bool svsReplace(int nElements, Block &block, AtDollar const &atd, 
                                                    char const *suffix);

        bool svsTagMem(int nElements, Block &block, AtDollar const &atd);
        bool svsTagPtr(int nElements, Block &block, AtDollar const &atd);
        bool svsTagRef(int nElements, Block &block, AtDollar const &atd);

        bool svsTagReplace(int nElements, Block &block, AtDollar const &atd, 
                                                    char const *suffix);


        std::string const &productionTag(int nr) const; // requires: nr > 0

//FBB        void checkExplicitTag(AtDollar const &atd) const;
//FBB        std::string callGet(AtDollar const &atd) const;

        void defaultAction() const;

        void constructorChecks() const;
        void warnTagMismatches() const;

        void addPolymorphic(std::string const &tag, 
                            std::string const &typeSpec);

        void addIncludeQuotes(std::string *target); // ensure ".." or <..> 
                                                    // around target name
        void checkEmptyBlocktype();
        void checkFirstType();

//FBB        bool noID(std::string const &) const;
//FBB        bool idOK(std::string const &) const;
//FBB        bool findTag(std::string const &tag) const;

//FBB        void returnSingle(AtDollar const &atd) const;
//FBB        std::string returnUnion(AtDollar const &atd) const;
//FBB        std::string returnPolymorphic(AtDollar const &atd) const;
 
//FBB        SemTag semTag(char const *label, AtDollar const &atd, 
//FBB              bool (Parser::*testID)(std::string const &) const) const;


        Symbol *defineNonTerminal(std::string const &name, 
                                  std::string const &stype);
        void definePathname(std::string *target);
        void defineTerminal(std::string const &name, Symbol::Type type);
        void defineTokenName(std::string const &name, bool hasValue);
        void expectRules();

        void setExpectedConflicts();
        void setLocationDecl();
        void setNegativeDollarIndices();
        void setPrecedence(size_t type);
        void setUnionDecl();
                                        

        size_t extractIndex(int *idx, size_t pos);
        size_t extractType(std::string *type, size_t pos, Block &block);

                                        // handles a location-value stack
                                        // reference (@) in a received action 
                                        // block
//FBB   void handleAtSign(Block &block, AtDollar const &atd, int nElements);

                                        // handles a semantic-value stack
                                        // reference ($) in a received action 
                                        // block
//FBB     bool handleDollar(Block &block, AtDollar const &atd, int nElements);

//FBB        void handleDeref(Block &block, AtDollar const &atd);

        STYPE__ handleProductionElements(STYPE__ &first, 
                                         STYPE__ const &second);
        void handleProductionElement(STYPE__ &last);


        void installAction(Block &block);

        void multiplyDefined(Symbol const *sp);

        void nestedBlock(Block &block); // define inner block as pseudo N

        std::string nextHiddenName();

            // may generate error or warning:
//FBB        void negativeIndex(AtDollar const &atd) const;

//FBB        void warnAutoOverride(AtDollar const &atd) const;
//FBB        void warnAutoIgnored(char const *typeOrField, 
//                             AtDollar const &atd) const;
//FBB        void warnUntaggedValue(AtDollar const &atd) const;

//        void errNoSemantic(char const *label, AtDollar const &atd,
// FBB?                                              std::string const &id) const;

        void setStart();
        void setPolymorphicDecl();

        void openRule(std::string const &ruleName);

        void predefine(Terminal const *terminal);   // Used by Parser() to 
                                                    // pre-enter into d_symtab

        NonTerminal *requireNonTerminal(std::string const &name);

                                        // saves the default $1 value
                                        // at the beginning of a mid-rule
                                        // action block (in substituteBlock)
//FBB        void saveDollar1(Block &block, int offset);


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

