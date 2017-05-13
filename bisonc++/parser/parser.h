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

    enum SemType        // s_autoTypeLable must be synchronized with this
    {                   // enum
        SINGLE,
        UNION,
        POLYMORPHIC
    };
    static char const *s_autoTypeLabel[];

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

    std::string d_field;                // %union field or %polymorphic
                                        // Tag__ value in %type specifications

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

    static std::string s_semanticValue; // name of the semantic value variable
                                        // used by the generated parser
    static std::string s_semanticValueStack;  
                                        // name of the semantic value stack
                                        // used by the generated parser
    static char s_locationValueStack[];  
                                    // name of the location value stack
                                    // used by the generated parser
    static char s_locationValue[];
                                    // name of the location value variable
                                    // used by the generated parser (@0)

    static std::string  s_stype;   // generic semantic value for POLYMORPHIC
                                    
    static std::string const s_undefined;


    static ADmap s_single;
    static ADmap s_union;
    static ADmap s_polymorphic;

    typedef void (Parser::*ActionBlockInstaller)(std::string const &ruleType, 
                                                 Production const &prod);

    static ActionBlockInstaller s_defaultAction[2][3][3];

    public:
        Parser(Rules &rules);
        int parse();
        void cleanup();             // do cleanup following parse();
        std::unordered_map<std::string, 
                           std::string> const &polymorphic() const;

    private:
        void updateDefaultActionLineNr();

        void checkField(std::string const &field);  // see inc/typename

        static void warnDefaultAction(Production const &prod);

        void installDefaultAction(Production const &prod, 
                                  std::string const &rhs);
        void defaultPolymorphicAction(Production const &prod);

        static std::string const &nameOf(std::string const &typeName);

            // see s_defaultAction[] for details
        static int typeIndex(std::string const &typeName);  // 0: "", 
                                                            // 1: s_stype
                                                            // 2: other types
            // no action block is installed
        void blkNop(std::string const &ruleType, Production const &prod);

            // no action block + error message
        void blkErr(std::string const &ruleType, Production const &prod);

            // a $$ = STYPE__{} action block
        void blkSTYPE(std::string const &ruleType, Production const &prod);

            // a $$ = $1.get... action block
        void blkAssign(std::string const &ruleType, Production const &prod);

            // a $$ = $1 action block
        void blkDirect(std::string const &ruleType, Production const &prod);

            // with equal types: blkAssign, otherwise blkErr
        void blkCheck(std::string const &ruleType, Production const &prod);


            // warns that no action block is installed
        void blkNopW(std::string const &ruleType, Production const &prod);

            // warns and blkSTYPE
        void blkSTYPEW(std::string const &ruleType, Production const &prod);

            // warns and blkAssign
        void blkAssignW(std::string const &ruleType, Production const &prod);

            // warns and blkDirect
        void blkDirectW(std::string const &ruleType, Production const &prod);

            // with equal types blkAssignW, otherwise blkErr
        void blkCheckW(std::string const &ruleType, Production const &prod);

        std::ostream &stdWmsg(AtDollar const &atd) const;
        std::ostream &stdEmsg(AtDollar const &atd) const;
        void warnNegativeDollarIndices(AtDollar const &atd) const;

        int indexToOffset(int idx, int nElements) const;
        bool existingTag(AtDollar const &atd) const;    // false and emsg if
                                                        // not an existing tag

        void errNoUnionPtr(AtDollar const &atd);
        bool errNoTag(int nElements, Block &block, AtDollar const &atd);
        bool errIndexTooLarge(AtDollar const &atd, int nElements) const;

        void warnForceLSP(size_t lineNr) const;
        void warnMissingSemval() const;

        void substituteBlock(int nElements, Block &block);

            // replacement members (see also handleProductionElement)
            // the dval*Replace return true for midRule actions, 
            // because that prevents the missingSemval warning.
        bool dvalReplace(bool midRule, Block &block, AtDollar const &atd, 
                                       char const *suffix);
        bool svsReplace(int nElements, Block &block, AtDollar const &atd, 
                                                    char const *suffix);
        bool dvalUnionReplace(bool midRule, Block &block, AtDollar const &atd, 
                                                    char const *suffix);
        bool svsUnionReplace(int nElements, Block &block, AtDollar const &atd, 
                                                    char const *suffix);
        bool dvalPolyReplace(bool midRule, Block &block, AtDollar const &atd, 
                                                    char const *suffix);
        bool svsPolyReplace(int nElements, Block &block, AtDollar const &atd, 
                                                    char const *suffix);

        bool svsUnionTagReplace(int nElements, Block &block, AtDollar 
                                            const &atd, char const *suffix);
        bool svsPolyTagReplace(int nElements, Block &block, AtDollar 
                                            const &atd, char const *suffix);

            // returns s_semanticValueStack[index]:
        std::string svsElement(int nElements, int nr) const; // nr, not index!

            // empty, or tag associated with a production rule's element
        std::string const &productionTag(int nr) const; // requires: nr > 0

            // $- and @-handlers
                                                                // @@
        bool loc(int nElements, Block &block, AtDollar const &atd);

                                                                // @nr
        bool locEl(int nElements, Block &block, AtDollar const &atd);

        // Wrt the dval* functions below:
        // 'refByScanner' means that the syntax used $$, but the scanner
        // changed that into _$$. In those cases mid-action rules should issue
        // warnings if the terminal has an associated type. Otherwise, an
        // explicit _$$ was used and no warning needs to be issued.
        
        // mid-rule actions (nElements < 0) should not issue missing Semval
        // warnings This is realized by returning true if nElements < 0

                                                                // $$
        bool dval(int nElements, Block &block, AtDollar const &atd);
        bool dvalUnion(int nElements, Block &block, AtDollar const &atd);
        bool dvalRefUnion(int nElements, Block &block, AtDollar const &atd);
        bool dvalPoly(int nElements, Block &block, AtDollar const &atd);

                                                                // $$(
        bool dvalPar(int nElements, Block &block, AtDollar const &atd);
        bool dvalUnionPar(int nElements, Block &block, AtDollar const &atd);
        bool dvalPolyPar(int nElements, Block &block, AtDollar const &atd);

                                                                // $$.
        bool dvalMem(int nElements, Block &block, AtDollar const &atd);
        bool dvalUnionMem(int nElements, Block &block, AtDollar const &atd);
        bool dvalPolyMem(int nElements, Block &block, AtDollar const &atd);

                                                                // $$->
        bool dvalPtr(int nElements, Block &block, AtDollar const &atd);
        bool dvalUnionPtr(int nElements, Block &block, AtDollar const &atd);
        bool dvalPolyPtr(int nElements, Block &block, AtDollar const &atd);

                                                        // $nr _$nr $-nr _$-nr
        bool svs(int nElements, Block &block, AtDollar const &atd);
        bool svsUnion(int nElements, Block &block, AtDollar const &atd);
        bool svsRefUnion(int nElements, Block &block, AtDollar const &atd);
        bool svsPoly(int nElements, Block &block, AtDollar const &atd);

                                                        // $nr. $-nr.
        bool svsMem(int nElements, Block &block, AtDollar const &atd);
        bool svsUnionMem(int nElements, Block &block, AtDollar const &atd);
        bool svsPolyMem(int nElements, Block &block, AtDollar const &atd);

                                                        // $nr-> $-nr->
        bool svsPtr(int nElements, Block &block, AtDollar const &atd);
        bool svsUnionPtr(int nElements, Block &block, AtDollar const &atd);
        bool svsPolyPtr(int nElements, Block &block, AtDollar const &atd);

                                                        // $<TAG>-nr
        bool svsUnionTag(int nElements, Block &block, AtDollar const &atd);
        bool svsPolyTag(int nElements, Block &block, AtDollar const &atd);

                                                        // $<TAG>-nr.
        bool svsUnionTagMem(int nElements, Block &block, AtDollar const &atd);
        bool svsPolyTagMem(int nElements, Block &block, AtDollar const &atd);

                                                        // $<TAG>-nr->
        bool svsUnionTagPtr(int nElements, Block &block, AtDollar const &atd);
        bool svsPolyTagPtr(int nElements, Block &block, AtDollar const &atd);


        // ================================================================

        void defaultAction() const;

        void constructorChecks() const;
        void warnTagMismatches() const;
        std::string warnAutoTag(bool midRule, AtDollar const &atd) const;

        void addPolymorphic(std::string const &tag, 
                            std::string const &typeSpec);

        void addIncludeQuotes(std::string *target); // ensure ".." or <..> 
                                                    // around target name
        void checkEmptyBlocktype();
        void checkFirstType();

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

        STYPE__ handleProductionElements(STYPE__ &first, 
                                         STYPE__ const &second);
        void handleProductionElement(STYPE__ &last);


        void installAction(Block &block);

        void multiplyDefined(Symbol const *sp);

        void nestedBlock(Block &block); // define inner block as pseudo N

        std::string nextHiddenName();

        void setStart();
        void setPolymorphicDecl();

        void openRule(std::string const &ruleName);

        void predefine(Terminal const *terminal);   // Used by Parser() to 
                                                    // pre-enter into d_symtab

        NonTerminal *requireNonTerminal(std::string const &name);

        Symbol *useSymbol();
        Terminal *useTerminal();

        void error();                   // called on (syntax) errors
        void exceptionHandler(std::exception const &exc);
        int lex();                      // returns the next token from the
                                        // lexical scanner. 
        void print();                   // use, e.g., d_token, d_loc
                                                         
                                                         
    // support functions for parse():                    
        void executeAction__(int ruleNr);                
        void errorRecovery__();                          
        void nextCycle__();                              
        void nextToken__();                              
        void print__();                                     
                                        // used in, e.g., handleDollar
                                        // to obtain # elements for
                                        // end- or mid-rule actions
        static int nComponents(int nElements);
};

// static 
inline std::string const &Parser::nameOf(std::string const &typeName)
{
    return typeName.empty() ? s_undefined : typeName;
}

inline std::unordered_map<std::string, 
                          std::string> const &Parser::polymorphic() const
{
    return d_polymorphic;
}

#endif

