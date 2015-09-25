#include "generator.ih"

string Generator::filename(std::string const &path)
{
    size_t idx = path.rfind('/');       
    
    string ret(idx == string::npos ? path : path.substr(idx + 1));

    return ret;
}
