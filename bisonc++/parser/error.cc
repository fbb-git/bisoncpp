#include "parser.ih"

void Parser::error(char const *msg)
{
    static bool repeated;
    static string lastMsg;

    if (d_msg.empty())
    {
        if (not repeated)
            lineMsg() << "unrecognized input (`" << d_scanner.YYText() << 
                         "') encountered" << err;
        repeated = true;
    }
    else
    {
        if (lastMsg != d_msg)
            lineMsg() << "at `" << d_scanner.YYText() << "': " << d_msg << 
                         " expected." << err;
        repeated = false;
    }

    lastMsg = d_msg;
}
