#include "msg.ih"

ostringstream &lineMsg()
{
    msg() << "Line " << Msg::s_line << ": ";
    return Msg::s_msg;
}
