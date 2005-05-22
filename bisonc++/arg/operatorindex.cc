#include "arg.ih"

char const *Arg::operator[](unsigned idx) const
{
    return
        (idx >= nArgs()) ?
            0
        :
            d_argv[idx].c_str();
}
