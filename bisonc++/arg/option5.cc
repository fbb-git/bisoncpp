#include "arg.ih"

bool Arg::option(string *value, char const *longOption) const
{
    unsigned idx = findopt(longOption);

    if (idx == nLongOptions())
        return false;

    string const &optval = d_longOption[idx].second;

    if (!value)
    {
        if (optval.length())
            throw Errno(EINVAL, 
                        "Arg::Option(): no storage for argument value");
        return true;
    }
    *value = optval;
    return true;
}
