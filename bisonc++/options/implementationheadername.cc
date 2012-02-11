#include "options.ih"

std::string Options::implementationHeaderName() const
{
    size_t pos = d_implementationHeaderPath.rfind('/');

    return pos == string::npos ? 
                        d_implementationHeaderPath 
                    :
                        d_implementationHeaderPath.substr(pos + 1);
}
