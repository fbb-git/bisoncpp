#include "parser.ih"

void Parser::noDefaultTypeWarning() const
{
    if (d_unionDeclared)
        lineMsg() << "$$ of `" << d_rules.name() << 
                 "' has no default type-association" << warning;
}
