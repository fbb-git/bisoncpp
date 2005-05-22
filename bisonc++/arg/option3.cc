#include "arg.ih"

bool Arg::option(std::string const &optchars) const
{
    for (char const *cp = optchars.c_str(); *cp; cp++)
    {
        if (option(*cp))
            return true;
    }
    return false;
}
