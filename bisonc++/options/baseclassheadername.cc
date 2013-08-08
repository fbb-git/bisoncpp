#include "options.ih"

std::string Options::baseclassHeaderName() const
{
    size_t pos = d_baseClassHeader.rfind('/');
    return pos == string::npos ? 
                        d_baseClassHeader
                    :
                        d_baseClassHeader.substr(pos + 1);
}
