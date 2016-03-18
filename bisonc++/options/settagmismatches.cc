#include "options.ih"

    // Resulting values: ON, OFF
void Options::setTagMismatches(string const &request,
                               string const &filename, size_t lineNr)
{
    Value value = valueOf(request, ON, ~WARN);
                                            // the mask turns WARN into ON
    if (value == QUIET)
        value = OFF;

    d_tagMismatches = OptInfo{value, filename, lineNr};
}

