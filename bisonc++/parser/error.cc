#include "parser.ih"

void Parser::error(char const *msg)
{
    static bool repeated;
    static string lastMsg;

    if (d_msg.empty())
    {
        if (not repeated)
            lineMsg(emsg) << "unrecognized input (`" << d_scanner.YYText() << 
                         "') encountered" << endl;
        repeated = true;
    }
    else
    {
        if (lastMsg != d_msg)
            lineMsg(emsg) << "at `" << d_scanner.YYText() << "': " << d_msg << 
                         " expected." << endl;
        repeated = false;
    }

    lastMsg = d_msg;
}
