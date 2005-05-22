#include "rules.ih"

streambuf *Rules::setVerbose(string const &filename) 
{
    if (!filename.length())
        return 0;

    Msg::open(d_verbose, filename.c_str());
    Msg::display();
    return infoToVerbose();
}
