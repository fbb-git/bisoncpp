#include "parser.ih"

Parser::ActionMap::value_type Parser::s_info[] = 
{
    Value(Scanner::BASECLASS_HEADER,    &Parser::setBaseclassHeader),
    Value(Scanner::BASECLASS_PREINCLUDE,&Parser::setPreInclude),
    Value(Scanner::CLASS_HEADER,        &Parser::setClassHeader),
    Value(Scanner::CLASS_NAME,          &Parser::setClassName),
    Value(Scanner::DEBUGFLAG,           &Parser::setDebugFlag),
    Value(Scanner::ENDFILE,             &Parser::unexpectedEOF),
    Value(Scanner::ERROR_VERBOSE,       &Parser::setErrorVerbose),
    Value(Scanner::EXPECT,              &Parser::setExpectedConflicts),
    Value(Scanner::FILENAMES,           &Parser::setGenericFilename),
    Value(Scanner::IMPLEMENTATION_HEADER,
                                    &Parser::setImplementationHeader),

    Value(Scanner::LEFT,                &Parser::setLeft),
    Value(Scanner::LINES,               &Parser::setLines),
    Value(Scanner::LOCATIONSTRUCT,      &Parser::setLocationDecl),
    Value(Scanner::LSP_NEEDED,          &Parser::setLspNeeded),
    Value(Scanner::LTYPE,               &Parser::setLtype),
    Value(Scanner::NAMESPACE,           &Parser::setNameSpace),
    Value(Scanner::NONASSOC,            &Parser::setNonAssoc),
    Value(Scanner::PARSEFUN_SOURCE,     &Parser::setParsefunSource),
    Value(Scanner::SCANNER_INCLUDE,     &Parser::setScannerInclude),
    Value(Scanner::RIGHT,               &Parser::setRight),
    Value(Scanner::STYPE,               &Parser::setStype),
    Value(Scanner::START,               &Parser::setStart),
    Value(Scanner::TOKEN,               &Parser::setToken),
    Value(Scanner::TYPE,                &Parser::setType),
    Value(Scanner::UNION,               &Parser::setUnionDecl),
    Value(Scanner::TWO_PERCENTS,        &Parser::done),
};

char Parser::s_defaultClassName[]         = "Parser";
char Parser::s_defaultParsefunSource[]  = "parse.cc";

Parser::ActionMap Parser::s_action
(
    s_info, 
    s_info + sizeof(s_info) / sizeof(Value)
);

unsigned Parser::s_nHidden;

ostringstream Parser::s_hiddenName;


char Parser::s_semanticValue[] = "d_val";   
                                    // name of the semantic value variable
                                    // used by the generated parser.
char Parser::s_semanticValueStack[] = "d_vsp";  
                                    // name of the semantic value stack
                                    // used by the generated parser
char Parser::s_locationValueStack[] = "d_lsp";  
                                    // name of the location value stack
                                    // used by the generated parser

