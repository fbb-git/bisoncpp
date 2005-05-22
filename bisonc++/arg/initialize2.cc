#include "arg.ih"

Arg &Arg::initialize(char const *optstring,
                LongOption const * const begin, 
                LongOption const * const end, 
                int argc, char **argv)
{
    if (s_arg)
        throw Errno("Arg::initialize(): already initialized");

    s_arg = new Arg(optstring, begin, end, argc, argv);
    return *s_arg;
}
