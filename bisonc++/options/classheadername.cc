#include "options.ih"

std::string Options::classHeaderName() const
{
    size_t pos = d_classHeaderPath.rfind('/');

    return pos == string::npos ? 
                        d_classHeaderPath 
                    :
                        d_classHeaderPath.substr(pos + 1);
}
