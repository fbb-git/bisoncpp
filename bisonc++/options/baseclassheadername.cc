#include "options.ih"

std::string Options::baseclassHeaderName() const
{
    size_t pos = d_baseClassHeaderPath.rfind('/');
    return pos == string::npos ? 
                        d_baseClassHeaderPath 
                    :
                        d_baseClassHeaderPath.substr(pos + 1);
}
