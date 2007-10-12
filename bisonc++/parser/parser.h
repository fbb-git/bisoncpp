#ifndef Parser_h_included
#define Parser_h_included

// $insert baseclass
#include "parserbase.h"
// $insert scanner.h
#include "../scanner/scanner.h"

class NonTerminal;
class Terminal;
class Symbol;

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

    FBB::Arg &d_arg;

    // $insert scannerobject
    Scanner d_scanner;
    Rules      &d_rules;
    Symtab      d_symtab;

    bool        d_debugFlag;
    bool        d_errorVerbose;
    bool        d_generateBaseclass;
    bool        d_lines;
    bool        d_lspNeeded;
    bool        d_negativeDollarIndices;
    bool        d_typeDirective;            // true following %type
    bool        d_unionDeclared;            // see setuniondecl.cc

    size_t      d_requiredTokens;

    std::string d_baseclassHeader;
    std::string d_baseclassSkeleton;
    std::string d_classHeader;
    std::string d_className;
    std::string d_classSkeleton;
    std::string d_field;                    // %union field in <type> specs.
    std::string d_genericFilename;
    std::string d_implementationHeader;
    std::string d_implementationSkeleton;
    std::string d_locationDecl;
    std::string d_msg;
    std::string d_nameSpace;
    std::string d_parsefunSkeleton;
    std::string d_parsefunSource;
    std::string d_preInclude;
    std::string d_scannerInclude;
    std::string d_stackDecl;
    std::string d_verboseName;

    Terminal::Association d_association;

                                // used in processBlock() and sipIgnore()
    std::vector<Block::Range>::const_reverse_iterator d_skipRbegin;
    std::vector<Block::Range>::const_reverse_iterator d_skipRend;

    static char s_defaultBaseclassSkeleton[];
    static char s_defaultClassName[];
    static char s_defaultClassSkeleton[];
    static char s_defaultImplementationSkeleton[];
    static char s_defaultParsefunSkeleton[];
    static char s_defaultParsefunSource[];

    static std::ofstream s_verbose;



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
        std::string const &baseclassHeader() const;
        std::string const &baseclassSkeleton() const;
        std::string const &classHeader() const;
        std::string const &className() const;
        std::string const &classSkeleton() const;
        bool errorVerbose() const;
        bool debugFlag() const;
        std::string const &implementationHeader() const;
        std::string const &implementationSkeleton() const;
        bool lines() const;
        bool lspNeeded() const;
        std::string const &ltype() const;
        std::string const &nameSpace() const;
        std::string const &parseSkeleton() const;
        std::string const &parseSource() const;
        std::string const &preInclude() const;
        size_t requiredTokens() const;
        std::string const &scanner() const;
        std::string const &stype() const;

    private:
        void addIncludeQuotes(std::string *target); // ensure ".." or <..> 
                                                    // around target name
        void checkEmptyBlocktype();
        void checkFirstType();

        std::ostream &lineMsg();
                                        
        bool defaultReturn(size_t pos, Block &block);
        Symbol *defineNonTerminal(std::string const &name, 
                                  std::string const &stype);
        void definePathname(std::string *target, int type); // 0: no undelimit
        void defineTerminal(std::string const &name, Symbol::Type type);
        void defineTokenName(std::string *name, bool hasValue);
        void expectRules();

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
        std::string *newYYText() const; // make dynamic copy of YYText()

        std::string nextHiddenName();
        void noDefaultTypeWarning();

        bool numberedElement(size_t pos, int nElements, Block &block);

        void openRule(std::string *ruleNamePtr);

        void predefine(Terminal const *terminal);   // Used by Parser() to 
                                                    // pre-enter into d_symtab

        NonTerminal *requireNonTerminal(std::string const &name);

        void setAccessorVariables();
        void setBaseclassHeader(int type);
        void setClassHeader(int type);
        void setClassName();
        void setPreInclude();
        void setDebugFlag();
        void setErrorVerbose();
        void setExpectedConflicts();
        void setGenericFilename(int type);
        void setImplementationHeader(int type);
        void setLines();
        void setLocationDecl();
        void setLspNeeded();
        void setLtype();
        void setName(std::string *target, char const *extension);
        void setNameSpace();
        void setNegativeDollar();
        void setParsefunSource(int type);
        void setPrecedence(int type);
        void setRequiredTokens();
        void setScannerInclude();
        void setStart();
        void setStype();

        void setUnionDecl();
        void setVerbosity();            // Prepare Msg for verbose output

        void showFilenames() const;

        size_t skipIgnore(size_t pos);
        bool substituteBlock(int nElements, Block &block);

        Symbol *useSymbol();
        Terminal *useTerminal();

        void validateInclude(std::string *target);

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
    return d_scanner.yylex();
}

inline std::string const &Parser::baseclassHeader() const
{
    return d_baseclassHeader;
}

inline std::string const &Parser::baseclassSkeleton() const
{
    return d_baseclassSkeleton;
}

inline std::string const &Parser::classHeader() const
{
    return d_classHeader;
}

inline std::string const &Parser::className() const
{
    return d_className;
}

inline std::string const &Parser::classSkeleton() const
{
    return d_classSkeleton;
}

inline bool Parser::debugFlag() const
{
    return d_debugFlag;
}

inline bool Parser::errorVerbose() const
{
    return d_errorVerbose;
}

inline std::string const &Parser::implementationHeader() const
{
    return d_implementationHeader;
}

inline std::string const &Parser::implementationSkeleton() const
{
    return d_implementationSkeleton;
}

inline std::ostream &Parser::lineMsg()
{
    return d_scanner.lineMsg();
}

inline bool Parser::lspNeeded() const
{
    return d_lspNeeded;
}
inline std::string const &Parser::ltype() const
{
    return d_locationDecl;
}
inline std::string const &Parser::nameSpace() const
{
    return d_nameSpace;
}

inline std::string const &Parser::parseSkeleton() const
{
    return d_parsefunSkeleton;
}

inline std::string const &Parser::parseSource() const
{
    return d_parsefunSource;
}

inline std::string const &Parser::preInclude() const
{
    return d_preInclude;
}

inline std::string const &Parser::scanner() const
{
    return d_scannerInclude;
}

inline void Parser::setBaseclassHeader(int type)
{
    definePathname(&d_baseclassHeader, type);
}

inline void Parser::setClassHeader(int type)
{
    definePathname(&d_classHeader, type);
}

inline void Parser::setPreInclude()
{
    validateInclude(&d_preInclude);
}

inline void Parser::setDebugFlag()
{
    d_debugFlag = true;
}

inline void Parser::setErrorVerbose()
{
    d_errorVerbose = true;
}

inline void Parser::setExpectedConflicts()
{
    Rules::setExpectedConflicts(d_scanner.number());
}

inline void Parser::setGenericFilename(int type)
{
    definePathname(&d_genericFilename, type);
}

inline void Parser::setImplementationHeader(int type)
{
    definePathname(&d_implementationHeader, type);
}

inline void Parser::setLines()
{
    d_lines = true;
}

inline void Parser::setLspNeeded()
{
    d_lspNeeded = true;
}

inline void Parser::setNegativeDollar()
{
    d_negativeDollarIndices = true;
}        

inline void Parser::setParsefunSource(int type)
{
    definePathname(&d_parsefunSource, type);
}

inline size_t Parser::requiredTokens() const
{
    return d_requiredTokens;
}

inline void Parser::setScannerInclude()
{
    validateInclude(&d_scannerInclude);
}

inline std::string const &Parser::stype() const
{
    return d_stackDecl;
}

inline std::string *Parser::newYYText() const
{
    return new std::string(d_scanner.YYText());
}

inline void Parser::print()      // use d_token, d_loc
{}

inline size_t Parser::nComponents(int nElements)
{
    return nElements >= 0 ? nElements : -nElements - 1;
}


#endif
