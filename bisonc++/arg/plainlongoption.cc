#include "arg.ih"

bool Arg::plainLongOption(int *c, Arg::LongOption const &longOption)
{
    d_longOption.push_back                  // long option was used: 
    (                                       // store it.    
        StringStringPair(longOption.d_name, optarg ? optarg : "")
    );

    if (!longOption.d_optionChar)           // it's a plain long option.
        return true;

    *c = longOption.d_optionChar;
    return false;                           // not a plain long option:
                                            // it's also a simple option.
}
