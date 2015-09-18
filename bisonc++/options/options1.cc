#include "options.hh"

Options::Options()
:
    d_arg(Arg::instance()),
    d_debug(false),
    d_errorVerbose(false),
    d_flex(false),
    d_lines(true),
    d_lspNeeded(false),
    d_printTokens(false),
    d_polymorphic(false),
    d_strongTags(true),
    d_requiredTokens(0),
    d_verboseName("(not requested)")
{}
