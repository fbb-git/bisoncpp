#include "parser.ih"

void Parser::error(char const *msg)
{
    static bool repeated;
    static string lastMsg;

    if (d_expect.empty())
    {
        if (not repeated)
            emsg << "unrecognized input (`" << d_scanner.YYText() << 
                         "') encountered" << endl;
        repeated = true;
    }
    else
    {
        if (lastMsg != d_expect)
            emsg << "at `" << d_scanner.YYText() << "': " << d_expect << 
                         " expected." << endl;
        repeated = false;
    }

    lastMsg = d_expect;
}
