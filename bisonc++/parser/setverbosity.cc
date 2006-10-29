#include "parser.ih"

void Parser::setVerbosity()
{
    if (!d_arg.option(0, "construction") && !d_arg.option('V'))
    {
        Msg::setInfoBuf(0);             // suppress verbose messages
        Msg::setDisplay(false);
        return;
    }

    d_verboseName = d_parsefunSource;      // determine the output filename
    size_t pos = d_verboseName.find_last_of(".");

    if (pos == string::npos)
        pos = d_verboseName.length();

    d_verboseName.resize(pos);
    d_verboseName += ".output";

    Msg::open(s_verbose, d_verboseName.c_str());
    Msg::setInfoBuf(s_verbose.rdbuf());
}
