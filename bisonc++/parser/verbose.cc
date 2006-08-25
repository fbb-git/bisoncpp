#include "parser.ih"

string Parser::verbose() const
{
    string ret = d_parsefunSource;
    size_t/*unsigned*/ pos = ret.find_last_of(".");
    if (pos == string::npos)
        pos = ret.length();

    ret.resize(pos);
    return ret + ".output";
}
