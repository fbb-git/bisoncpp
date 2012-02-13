#include "options.ih"

Options::Options()
:
    d_arg(Arg::instance()),
//    d_lines(true),
    d_verboseName("(not requested)"),
    d_debug(false),
    d_errorVerbose(false),
    d_flexcpp(false),
    d_lines(false),
    d_requiredTokens(0)
{}
