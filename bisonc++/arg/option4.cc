#include "arg.ih"

bool Arg::option(string *value, int optchar) const
{
    unsigned idx = findopt(optchar);

    if (idx == nOptions())
        return false;

    *value = d_optv[idx].second;
    return true;
}
