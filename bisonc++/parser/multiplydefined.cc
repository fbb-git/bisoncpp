#include "parser.ih"

void Parser::multiplyDefined(Symbol const *sp, string const &name) const
{
    lineMsg() << OM::ext  << sp << " multiply defined" << err;
}
