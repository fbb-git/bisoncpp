#include "parser.hh"

void Parser::reset() 
{
    d_rpn.clear();
    d_rpn.str(string());
}
