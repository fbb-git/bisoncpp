#include "options.ih"

void Options::setDefaultAction(string const &request,
                               string const &filename, size_t lineNr)
{
    Value value = valueOf(request, WARN, ~ON); // the mask turns ON into WARN

    d_defaultActions = OptInfo{value, filename, lineNr};
}

