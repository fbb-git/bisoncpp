#ifndef _INCLUDED_PARSER_
#define _INCLUDED_PARSER_

#include <map>
#include <sstream>

#include <bobcat/msg>
#include "../symtab/symtab.h"
#include "../block/block.h"
#include "../scanner/scanner.h"
#include "../terminal/terminal.h"
#include "../rules/rules.h"

namespace FBB
{
    class Arg;
}

class Parser
{
            // actions to taken given tokens returned by the lexical scanner
    typedef std::map<unsigned, void (Parser::*)()> 
            ActionMap;
    typedef ActionMap::iterator 
            Iterator;
    typedef ActionMap::value_type 
            Value;

    static ActionMap::value_type s_info[];
    static ActionMap s_action;

    static char s_defaultBaseclassSkeleton[];
    static char s_defaultClassName[];
    static char s_defaultClassSkeleton[];
    static char s_defaultImplementationSkeleton[];
    static char s_defaultParsefunSkeleton[];
    static char s_defaultParsefunSource[];

    static unsigned s_nHidden;          // number of hidden nonterminals
    static std::ostringstream s_hiddenName;

    static char s_semanticValue[];  // name of the semantic value variable
                                    // used by the generated parser
    static char s_semanticValueStack[];  
                                    // name of the semantic value stack
                                    // used by the generated parser
    static char s_locationValueStack[];  
                                    // name of the location value stack
                                    // used by the generated parser

    FBB::Arg &d_arg;

    Block       d_block;        // last processed block. Must be handled
                                // before d_scanner.block() is called

    Rules      &d_rules;
    Scanner     d_scanner;
    Symtab      d_symtab;

    bool        d_debugFlag;
    bool        d_errorVerbose;
    bool        d_generateBaseclass;
    bool        d_lines;
    bool        d_lspNeeded;
    bool        d_negativeDollarIndices;
    bool        d_unionDeclared;            // see setuniondecl.cc
    std::string d_baseclassHeader;
    std::string d_baseclassSkeleton;
    std::string d_classHeader;
    std::string d_className;
    std::string d_classSkeleton;
    std::string d_genericFilename;
    std::string d_implementationHeader;
    std::string d_implementationSkeleton;
    std::string d_locationDecl;
    std::string d_nameSpace;
    std::string d_parsefunSkeleton;
    std::string d_parsefunSource;
    std::string d_preInclude;
    std::string d_scannerInclude;
    std::string d_stackDecl;

                                // used in processBlock() and sipIgnore()
    std::vector<Block::Range>::const_reverse_iterator d_skipRbegin;
    std::vector<Block::Range>::const_reverse_iterator d_skipRend;

    public:
        Parser(Rules &rules);
        void parse();

        // public accessors

        std::string const &baseclassHeader() const
        {
            return d_baseclassHeader;
        }
        std::string const &baseclassSkeleton() const
        {
            return d_baseclassSkeleton;
        }
        std::string const &classHeader() const
        {
            return d_classHeader;
        }
        std::string const &className() const
        {
            return d_className;
        }
        std::string const &classSkeleton() const
        {
            return d_classSkeleton;
        }
        bool debugFlag() const
        {
            return d_debugFlag;
        }
        std::string const &implementationHeader() const
        {
            return d_implementationHeader;
        }
        std::string const &implementationSkeleton() const
        {
            return d_implementationSkeleton;
        }
        bool lines() const;
        bool lspNeeded() const
        {
            return d_lspNeeded;
        }
        std::string const &ltype() const
        {
            return d_locationDecl;
        }
        std::string const &nameSpace() const
        {
            return d_nameSpace;
        }
        std::string const &parseSkeleton() const
        {
            return d_parsefunSkeleton;
        }
        std::string const &parseSource() const
        {
            return d_parsefunSource;
        }
        std::string const &preInclude() const
        {
            return d_preInclude;
        }
        std::string const &scanner() const
        {
            return d_scannerInclude;
        }
        void showFilenames() const;
        std::string const &stype() const
        {
            return d_stackDecl;
        }
        std::string verboseSource() const;

    private:
        void checkBlocktype();

                                        // called from handleDollar
        bool defaultReturn(unsigned pos);

        void definePathname(std::string *sp);

        Symbol *defineNonTerminal(std::string const &name, 
                                  std::string const &stype);

        void defineTerminal(std::string const &name, 
                            Symbol::Type type,
                            Terminal::Association association, 
                            std::string stype);

        int elementNr(unsigned *idx, std::string const &text);

                                        // called from handleDollar
        bool explicitElement(unsigned pos, unsigned nElements);
        bool explicitReturn(unsigned pos);

        unsigned extractType(std::string *type, unsigned pos);
        unsigned extractIndex(int *idx, unsigned pos) const;

        void handleAtSign(unsigned idx, unsigned nElements);
                                        // handle a location-value stack
                                        // reference (@) in a received action 
                                        // block

        void handleBlock();             // process a `{ block }', 
                                        // part of a rule-production

        bool handleDollar(unsigned idx, unsigned nElements);
                                        // handle a semantic-value stack
                                        // reference ($) in a received action 
                                        // block
        void handleIdent();             // add symbolic token to a 
                                        // rule-production
        void handleQuote();             // add char-token to a 
                                        // rule-production
        int indexToOffset(int idx, unsigned nElements) const;
        void multiplyDefined(Symbol const *sp, std::string const &name) const;
        void nestedBlock();
        void newProduction();
        std::string nextHiddenName();

        void noDefaultTypeWarning() const;

                                        // called from handleDollar
        bool numberedElement(unsigned pos, unsigned nElements);


        void parseAssociations(Terminal::Association association);
        void parseDeclarations();

        void parseGrammar();            // the full grammar specification 
        void parseRule();               // all productions of a rule

        void predefine(Terminal const *terminal);   // Used by Parser() to 
                                                    // pre-enter into d_symtab

        void substituteBlock(unsigned nElements);  
                                        // replace @ and $ in blocks by 
                                        // variables, knowing that we've seen
                                        // `nElements' elements in the current
                                        // production rule

        void setAccessorVariables();
        void setName(std::string *target, char const *extension);
        void setNegativeDollar()
        {
            d_negativeDollarIndices = true;
        }        
        void setPrecedence();               // called by parseProduction()
        void showEmpty() const;
        unsigned skipIgnore(unsigned pos);  // used by processBlock()

                                        // in setType():
        void tryNonTerminal(std::string const &name, 
                            std::string const &stype);

                                        // remove '< ' and ' >' around types
        void getType(std::string *sp) const;
        NonTerminal *useNonTerminal();
        Symbol *useSymbol();            // use a symbol, assume N-term if not
                                        // existing
        Terminal *useTerminal();

                                        // install the action block for the
                                        // currently defined production
        void installAction();   

        // SUPPORT FUNCTIONS (for s_actions[])

        void done();
        void junk();
        void unexpectedEOF()
        {
            d_scanner.unexpectedEOF();
        }
        void setBaseclassHeader()
        {
            definePathname(&d_baseclassHeader);
        }
        void setClassHeader()
        {
            definePathname(&d_classHeader);
        }
        void setClassName();
        void setDebugFlag()
        {
            d_debugFlag = true;
        }
        void setErrorVerbose()
        {
            d_errorVerbose = true;
        }
        void setExpectedConflicts();
        void setGenericFilename()
        {
            definePathname(&d_genericFilename);
        }
        void setImplementationHeader()
        {
            definePathname(&d_implementationHeader);
        }
        void setLeft()
        {
            parseAssociations(Terminal::LEFT);
        }
        void setLines()
        {
            d_lines = true;
        }
        void setLtype();
        void setLocationDecl();
        void setLspNeeded()
        {
            d_lspNeeded = true;
        }
        void setNameSpace();
        void setNonAssoc()
        {
            parseAssociations(Terminal::NONASSOC);
        }
        void setParsefunSource()
        {
            definePathname(&d_parsefunSource);
        }
        void setPreInclude()
        {
            validateInclude(&d_preInclude);
        }
        void setScannerInclude()
        {
            validateInclude(&d_scannerInclude);
        }

        void setRight()
        {
            parseAssociations(Terminal::RIGHT);
        }
        void setStart();
        void setStype();
        void setType();
        void setToken();
        void setUnionDecl();

        void validateInclude(std::string *target);
        std::string verbose() const;
};
        
#endif
