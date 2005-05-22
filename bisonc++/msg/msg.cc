#include "msg.ih"

ostringstream &msg()
{
    Msg::s_msg.clear();
    Msg::s_msg.str("");
    return Msg::s_msg;
}
