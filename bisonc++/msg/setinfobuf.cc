#include "msg.ih"

streambuf *Msg::setInfoBuf(streambuf *newBuffer, bool display)
{
    s_display = display;

    return s_info.rdbuf(newBuffer ? newBuffer : s_info.rdbuf());
}
