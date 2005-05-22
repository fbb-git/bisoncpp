#include "msg.ih"

bool Msg::setDisplay(bool mode) 
{
    bool old = s_display;
    s_display = mode;
    return old;
}
