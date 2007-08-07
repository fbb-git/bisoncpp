#include "parser.ih"

char Parser::s_defaultClassName[]         = "Parser";
char Parser::s_defaultParsefunSource[]  = "parse.cc";

size_t Parser::s_nHidden;

ostringstream Parser::s_hiddenName;


char Parser::s_semanticValue[] = "d_val__";   
                                    // name of the semantic value variable
                                    // used by the generated parser.
char Parser::s_semanticValueStack[] = "d_vsp__";  
                                    // name of the semantic value stack
                                    // used by the generated parser
char Parser::s_locationValueStack[] = "d_lsp__";  
                                    // name of the location value stack
                                    // used by the generated parser

ofstream Parser::s_verbose;         // stream to contain verbose output
