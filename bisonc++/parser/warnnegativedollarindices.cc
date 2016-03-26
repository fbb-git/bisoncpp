#include "parser.ih"

void Parser::warnNegativeDollarIndices(AtDollar const &atd) const
{
    if (d_negativeDollarIndicesOK || atd.nr() > 0)
        return;

    stdWmsg(atd) << "negative $-index used in action block `" << atd.text() << 
                                                                '\'' << endl;
}
