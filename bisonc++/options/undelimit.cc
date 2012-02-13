#include "options.ih"

string Options::undelimit(std::string const &str)
{
    string ret = String::unescape(
                    str.find("<\"") != 0  ?  
                        str
                    : 
                        str.substr(1, str.size() - 2)
                );

    return ret;
}
