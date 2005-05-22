/*
                              errno.cc
*/

#include "errno.ih"

Errno::Errno(char const *prefix)
:
    d_errno(errno),
    d_msg(prefix ? prefix : "")
{
    initMsg();
}
