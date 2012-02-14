#include "options.ih"

Options::Options()
:
    d_arg(Arg::instance()),
    d_debug(false),
    d_errorVerbose(false),
    d_flexcpp(false),
    d_lines(true),
    d_lspNeeded(false),
    d_useMatchForPrint(false),
    d_requiredTokens(0),
    d_verboseName("(not requested)")
{}
