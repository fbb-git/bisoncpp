/*
                              errno.cc

   $Id$

   $Log$
   Revision 1.1  2005/05/22 14:02:15  frank
   Initial revision

   Revision 1.1.1.1  2003/05/28 13:32:23  frank
   Initial installation of FBB::Errno

*/

#include "errno.ih"

Errno::Errno()
:
    d_errno(errno)
{
    initMsg();
}
