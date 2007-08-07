#include "parser.ih"

void Parser::setVerbosity()
{
    if (!d_arg.option(0, "construction") && !d_arg.option('V'))
    {
        Msg::setInfoBuf(0);             // suppress verbose messages
        Msg::setDisplay(false);
        return;
    }
                                        // determine the output filename
    (d_verboseName = d_arg[0]) += ".output";

    Msg::open(s_verbose, d_verboseName.c_str());
    Msg::setInfoBuf(s_verbose.rdbuf());
}
