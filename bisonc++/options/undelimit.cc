#include "options.ih"

string Options::undelimit()
{
    string ret = String::unescape(
                    d_matched->find("<\"") != 0  ?  
                        *d_matched 
                    : 
                        d_matched->substr(1, str.size() - 2)
                );

    return ret;
}
