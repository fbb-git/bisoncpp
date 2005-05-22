/*
                              getoptlong.cc

   $Id$

   $Log$
   Revision 1.1  2005/05/22 14:02:15  frank
   Initial revision

   Revision 1.1.1.1  2003/05/28 13:50:17  frank
   Initial import of FBB::Arg

*/

#include "getoptlong.h"

#ifndef _SYSINC_CSTDLIB_
#include <cstdlib>
#define _SYSINC_CSTDLIB_
#endif

#ifndef _SYSINC_GETOPT_H_
#include <getopt.h>
#define _SYSINC_GETOPT_H_
#endif

using namespace std;
using namespace FBB;


int main(int argc, char **argv, char **envp)
{
    int value;

    opterr = 0;

    struct option longopts [] =
    {
        {"a-opt", 0, 0, 'a'},
        {"one", 0, &value, 100},
        {"two", 0, &value, 200},
        {0, }
    };

    while (true)
    {
        int c = getopt_long(argc, argv, "abc", longopts, 0);
        char ch = c;
        char co = optopt;

        switch (c)
        {
            case EOF:
                cout << "All processed\n";
            return 0;

            case ':':
                cout << "ArgData::ArgData(): missing option value" << endl;
            break;

            case '?':
                cout << "ArgData::ArgData(): unknown option"  <<
                                optopt << " (" << co << ")" << endl;
            break;

            case 0:
                cout << "0 return. val = " << value << endl;
            break;

            default:
                cout << "Default return. c = " << ch << ", optopt = " <<
                                    optopt << endl;
            break;    
        }
    }
}



