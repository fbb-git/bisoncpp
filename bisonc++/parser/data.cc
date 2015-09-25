#include "parser.ih"

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
char Parser::s_locationValue[] = "d_loc__";  
                                    // name of the location value variable
                                    // used by the generated parser (@0)

char const Parser::s_stype__[] = "STYPE__";
                                    // generic semantic value for POLYMORPHIC




