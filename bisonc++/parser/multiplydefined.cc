#include "parser.ih"

void Parser::multiplyDefined(Symbol const *sp, string const &name) const
{
    lineMsg() << Symbol::showType(sp) << " `" << name << 
                "' multiply defined" << err;
}
