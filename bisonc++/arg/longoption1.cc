#include "arg.ih"

Arg::LongOption::LongOption(char const *name, Type type)
:
    d_name(name),
    d_type(type),
    d_optionChar(0)        
{}
