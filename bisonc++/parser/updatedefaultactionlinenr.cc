#include "parser.ih"

void Parser::updateDefaultActionLineNr() 
{
    d_rules.updateDefaultActionLineNr(d_scanner.lineNr());
}
