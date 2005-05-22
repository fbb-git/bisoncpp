/*
                              driver.cc

   $Id$

   $Log$
   Revision 1.1  2005/05/22 14:02:15  frank
   Initial revision

   Revision 1.1.1.1  2003/05/28 13:32:23  frank
   Initial installation of FBB::Errno

*/

#ifndef _SYSINC_IOSTREAM_
#include <iostream>
#define _SYSINC_IOSTREAM_
#endif

#ifndef _INCLUDED_ERRNO_H_
#include "../errno.h"
#endif

#ifndef _SYSINC_ERRNO_H_
#include <errno.h>
#define _SYSINC_ERRNO_H_
#endif

using namespace std;
using namespace FBB;


int main(int argc, char **argv, char **envp)
{
    string hello = "hello world";

    try
    {
        try
        {
            Errno e;
            e << hello;
            throw e;
        }
        catch(Errno const &e)
        {
            cerr << e.what() << ", " << e.which() << "\n";
            throw;
        }
    }
    catch(exception const &e)
    {
        cout << "Exception caught: " << e.what() << "\n";
    }

    cerr << "================== second example ===============\n";

    try
    {
        errno = 12;
        Errno e("Prefix text");
        e << ".\n\tThis is the result of errno = " << errno;
        throw e;
    }
    catch(exception const &e)
    {
        cout << "Exception caught: " << e.what() << "\n";
    }

    cerr << "================== third example ===============\n";

    try
    {
        Errno e(12, "Prefix text");
        e << ".\n\tThis is the result of 12 prefixed initialized";
        throw e;
    }
    catch(Errno const &e)
    {
        cout << "Exception caught: " << e.what() << ", " << e.which() << "\n";
    }

    cerr << "================== fourth examplle ===============\n";

    try
    {
        throw Errno(99, "Special") << insertable << ". Hello world" << 
                                                    throwable;

        cerr << "NOT REACHED\n";
    }
    catch (exception &e)
    {
        cerr << e.what() << ".\n";
    }

/*
    This won't compile, as the result is an ostream, 
    which can't be copied.

    try
    {
        throw Errno(99, "Thrown: ") << unConst <<
                " a Errno object into which something is inserted";
    }
    catch (Errno const &e)
    {
        cout << e.what() << " " << e.why() << endl;
    }

    catch (ostream const &str)
    {
        cout << "stream is thrown\n";
    }
*/
}






