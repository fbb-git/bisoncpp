/*
                              initmsg.cc
*/

#include "errno.ih"

void Errno::initMsg()
{
    if (d_errno)
    {
        string msg = strerror(d_errno);

        if (d_msg.length())
            d_msg  += ": " + msg;
        else
            d_msg = msg;
    }
}
