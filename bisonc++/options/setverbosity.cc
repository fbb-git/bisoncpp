#include "options.ih"

void Options::setVerbosity()
{
    if 
    (
        d_arg.option('V') || d_arg.option(0, "construction") 
        ||
        d_arg.option(0, "own-debug")
    )
    {                                // determine the output filename
        (d_verboseName = d_arg[0]) += ".output";
        imsg.reset(d_verboseName);
    }
    else
        imsg.off();                 // suppress verbose messages
}
