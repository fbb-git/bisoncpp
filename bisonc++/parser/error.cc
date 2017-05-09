#include "parser.ih"

void Parser::error()
{
    static bool repeated;
    static string lastMsg;

    if (d_expect.empty())
    {
        if (not repeated)
            emsg << "unrecognized input (`" << d_matched << 
                         "') encountered." << endl;
        repeated = true;
    }
    else
    {
        if (lastMsg != d_expect)
            emsg << "at `" << d_matched << "': " << d_expect << 
                         " expected." << endl;
        repeated = false;
    }

    lastMsg = d_expect;
}
