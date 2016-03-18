#include "options.ih"

void Options::setDefaultAction(string const &request,
                               string const &filename, size_t lineNr)
{
    Value value = valueOf(request, WARN, ~ON); // the mask turns ON into WARN

    // OFF is off, QUIET is on without warning. 
    // ON -> WARN, WARN is on + warning

    d_defaultActions = OptInfo{value, filename, lineNr};
}

