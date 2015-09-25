#include "options.ih"

string Options::undelimit(std::string const &str)
{
    string ret = String::unescape(
                                    // no initial " or < then use str
                    string("<\"").find(str[0]) == string::npos  ?  
                        str
                    :               // else remove the 1st and last char
                        str.substr(1, str.size() - 2)
                );

    return ret;
}
