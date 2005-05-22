/*
                              driver.cc

   $Id$

   $Log$
   Revision 1.1  2005/05/22 14:02:15  frank
   Initial revision

   Revision 1.1.1.1  2003/05/28 13:50:17  frank
   Initial import of FBB::Arg

*/

#include "driver.h"

#ifndef _SYSINC_ALGORITHM_
#include <algorithm>
#define _SYSINC_ALGORITHM_
#endif

#ifndef _INCLUDED_ARG_H_
#include "../arg.h"
#endif

#ifndef _INCLUDED_ERRRNO_H_
#include "../../errno/errno.h"
#endif


using namespace std;
using namespace FBB;

void optcheck(char c)
{
    Arg &arg = Arg::getInstance();

    if (arg.option(c))
        cout << "Saw option " << c << endl;

    if (find("def", "def" + 3, c) != "def" + 3)
    {
        string value;
        if (arg.option(&value, c))
            cout << "option value of " << c << " is " << value << endl;
    }
}

void longopt(char const *longOpt)
{
    string value;
    Arg &arg = Arg::getInstance();

    bool opt =  arg.option(&value, longOpt);
    if (!opt)
        return;
   
    cout << longOpt << ":\t" <<
                (value.length() ? value : "-- no arg--") << endl;
}

int main(int argc, char **argv)
{
    Arg::LongOption lo[] =
    {
        Arg::LongOption("optional", Arg::Optional),
        Arg::LongOption("extra", Arg::Required),
        Arg::LongOption("file", 'f'),
        Arg::LongOption("version"),
        Arg::LongOption("add", 'a')
    };
    try
    {    
        Arg::initialize("abcd:e:f:", 
                lo, lo + 5,
                argc, argv);
    
        Arg &arg = Arg::getInstance();

        cout << "Program name is " << arg.basename() << endl;
    
        for_each("abcdefg", "abcdefg" + 7, optcheck)
            ;

        for (unsigned idx = 0; idx < arg.nArgs(); idx++)
            cout << "Argument " << idx << " = " << arg[idx] << endl;

        cout << "Long options:\n" << dec;

        longopt("optional");
        longopt("extra");
        longopt("file");
        longopt("version");
        longopt("add");

    }
    catch (Errno const &e)
    {
        cout << e.which() << " " << e.what() << endl;
    }

    return 0;
}
