#include "options.ih"

void Options::setOpt(string *destVar, 
                       char const *option, string const &defaultSpec)
{
    string str;

    d_arg.option(&str, option);

    if (not str.empty())
    {
        d_warnOptions.insert(option);
        *destVar = undelimit(str);
    }
    else if (destVar->empty())
        *destVar = defaultSpec;
}
