/*
                              errno.cc
*/

#include "errno.ih"

Errno::Errno(int err, char const *text)
:
    d_errno(err),
    d_msg(text ? text : "")
{}
