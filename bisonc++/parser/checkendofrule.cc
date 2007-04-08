#include "parser.ih"

void Parser::checkEndOfRule() const
{
    if (not d_lastRule.empty())
        lineMsg() << "Rule `" << d_lastRule << "' needs ending ';'" << err; 
}
