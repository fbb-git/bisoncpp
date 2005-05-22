#include "parser.ih"

void Parser::junk()
{
    lineMsg() << "junk (`" << d_scanner.text() << 
                 "') encountered in the declaration section" << err;

    d_scanner.ignoreUntilEndl();
}

