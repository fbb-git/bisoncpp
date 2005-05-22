#include "arg.ih"

void Arg::setBasename(string const &argv0)
{
    string::size_type idx = argv0.rfind(s_dirsep);

    d_base = idx == string::npos ? argv0 : argv0.substr(idx + 1);
}
