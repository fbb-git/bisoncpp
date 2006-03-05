#include "parser.ih"

void Parser::noDefaultTypeWarning() const
{
    lineMsg() << "$$ of `" << d_rules.name() << 
                 "' has no default type-association" << warning;
}
