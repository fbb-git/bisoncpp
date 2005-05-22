#include "rules.ih"

streambuf *Rules::infoToVerbose() const
{
    return                              // Peculiar: is_open() isn't const...
        const_cast<ofstream &>(d_verbose).is_open() ? 
            Msg::setInfoBuf(d_verbose.rdbuf()) 
        :
            0;
}
