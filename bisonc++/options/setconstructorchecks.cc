#include "options.ih"

void Options::setConstructorChecks(string const &request,
                                string const &filename, size_t lineNr)
{
    Value value = valueOf(request, ON, OFF);    // default ON, OFF also OK

    d_constructorChecks = OptInfo{value, filename, lineNr};
}
