#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"

#include <unordered_map>
#include <limits>

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
    typedef std::map<size_t, void (Parser::*)()>    ActionMap;
    typedef ActionMap::iterator                     Iterator;
    typedef ActionMap::value_type                   Value;

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
    std::map<std::string, std::string> d_polymorphic;

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
        std::map<std::string, std::string> const &polymorphic() const;

    private:
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

//        bool dollarIndex(size_t pos, int nElements, Block &block);
//        std::string dollarIndexUnion(Block const &block, size_t pos,
//                                    size_t nRuleElments, int idx, 
//                                    std::string const &elementType) const;
//        std::string dollarIndexPolymorphic(Block const &block, size_t pos, 
//                                size_t nRuleElments, int idx, 
//                                std::string const &typeTag) const;
//
//        bool dollarTypedDollar(size_t pos, Block &block);
//        std::string dollarTypedDollarUnion(std::string const &typeSpec) const;
//        std::string dollarTypedDollarPolymorphic(
//                                        std::string const &typeSpec) const;
//
//        bool dollarTypedIndex(size_t pos, int nElements, Block &block);
//        std::string dollarTypedIndexUnion(
//                        size_t nElements, int idx, std::string const &autoField, 
//                        std::string const &unionField) const;
//        std::string dollarTypedIndexPolymorphic(
//                        size_t nElements, int idx, std::string const &autoField, 
//                        std::string const &tagName) const;

                        // warns/true if a member is called (at $$. or $NR.)
        bool callsMember(char const *typeOrField, AtDollar const &atd) const;

                        // false if idx > nElements
        bool dollarIdx(int idx, size_t nElements) const;

        SemTag semTag(char const *label, AtDollar const &atd, 
                     bool (Parser::*testID)(std::string const &) const) const;

//            // Suffixes specify the members calling the semTag function:
//            // D: Dollar, T: Typed, I: Index, U: Union
//        SemTag semTagDDP() const;
//        SemTag semTagDIP(size_t nElements, int idx, 
//                                        std::string const &tagName) const;
//        SemTag semTagDIU(size_t nElements, int idx, 
//                                        std::string const &unionField) const;
//        SemTag semTagDTaux(std::string const &tagName) const;
//        SemTag semTagDTDP(std::string const &specifiedType) const;
//        SemTag semTagDTIP(size_t nElements, std::string const &autoTag, 
//                            int idx, std::string const &tagName) const;
//        SemTag semTagDTDU(std::string const &specifiedType) const;
//        SemTag semTagDTIU(size_t nElements, std::string const &autoField, 
//                            int idx, std::string const &unionField) const;

//                    // pos must be the position of the last $-related
//                    // specification. It can be, e.g., $$, $-1, $3
//                    // if the next non-blank char equals '.' then a member is
//                    // called and no replacement should be performed: false is
//                    // returned. False is also returned when 
//                    // defaultType == STYPE__ 
//        bool replaceDollar(Block const &block, size_t pos, 
//                           std::string const &defaultType);   

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

        void negativeIndex(AtDollar const &atd) const;
        void warnNoAuto(char const *typeOrField, AtDollar const &atd) const;

//        void warnAutoOverride(char const *typeOrField,
//                                std::string const &override) const;
        void warnAutoIgnored(char const *typeOrField, 
                             AtDollar const &atd) const;

        // generating emsgs:
        void noSTYPEtypeAssociations() const;
        void errNoSemantic(char const *label, std::string const &tag) const;
//      void errInvalidAuto(AtDollar const &atd) const;

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
                                        // used in, e.g., explicitElement()
                                        // to obtain # elements for
                                        // end- or mid-rule actions
        static size_t nComponents(int nElements);
};

inline std::map<std::string, std::string> const &Parser::polymorphic() const
{
    return d_polymorphic;
}

#endif

