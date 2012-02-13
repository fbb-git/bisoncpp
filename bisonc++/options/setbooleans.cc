#include "options.ih"

void Options::setBooleans()
{
    if (d_arg.option('d'))
        d_debug = true;

    if (d_arg.option(0, "error-verbose"))
        d_errorVerbose = true;

    if (d_arg.option(0, "flexcpp"))
        d_flexcpp = true;

    if (d_arg.option(0, "no-lines"))
        d_lines = false;
}
