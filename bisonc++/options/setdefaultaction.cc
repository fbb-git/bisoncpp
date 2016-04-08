#include "options.ih"

    // see also parser/expectrules.cc
void Options::setDefaultAction(string const &request,
                               string const &filename, size_t lineNr)
{
    Value value = valueOf(request, STD, ~STD); 

    if (value == ON)
        value = WARN;

    // OFF      -> off, 
    // QUIET    -> on without warning. 
    // WARN     -> ON + warning
    // ALWAYS   -> Does $$ = $1, no warnings (default)

    d_defaultActions = OptInfo{value, filename, lineNr};
}

