// Recompile this file if the skeleton locations in INSTALL.im change


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

#include "SKEL"

char Parser::s_defaultBaseClassSkeleton[]       = _Skel_ "/bisonc++base.h";
char Parser::s_defaultClassSkeleton[]           = _Skel_ "/bisonc++.h";
char Parser::s_defaultImplementationSkeleton[]  = _Skel_ "/bisonc++.ih";
char Parser::s_defaultParsefunSkeleton[]        = _Skel_ "/bisonc++.cc";




