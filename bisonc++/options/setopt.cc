#include "options.ih"

string Options::setOpt(char const *option, string const &defaultSpec)
{
    string ret;

    d_arg.option(&ret, option);

    if (ret.empty())
        ret = defaultSpec;
    else
    {
        d_warnOptions.insert(option);
        ret = undelimit(ret);
    }
        
    return ret;
}
