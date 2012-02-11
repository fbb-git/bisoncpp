#include "options.ih"

string Options::undelimit(string const &str)
{
    string ret = 
            str.find('"') != 0  ?  str : str.substr(1, str.size() - 2);

    return ret;
}
