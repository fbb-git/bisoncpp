#include "options.ih"

void Options::setVerbosity()
{
    if (!d_arg.option(0, "construction") && !d_arg.option('V'))
    {
        imsg.off();                     // suppress verbose messages
        return;
    }
                                        // determine the output filename
    (d_verboseName = d_arg[0]) += ".output";
    imsg.reset(d_verboseName);
}
