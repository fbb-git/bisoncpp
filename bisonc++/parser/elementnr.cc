#include "parser.ih"

int Parser::elementNr(unsigned *idx, string const &text) 
{
    istringstream istr(text.c_str() + *idx);
    int nr;

    if (!(istr >> nr))              // text ends prematurely
        throw 1;

    if (nr > 0)
    {
        *idx += istr.tellg();
        return nr;
    }

    lineMsg() << 
        "rule `" << d_rules.name() << "': [$@]" << nr << 
        " not supported. $- and @-values must be postive" << err;

    throw false;
}
