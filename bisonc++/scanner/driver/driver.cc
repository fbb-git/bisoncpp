/*
                              driver.cc
*/

#include "driver.h"

using namespace std;
using namespace FBB;

#include "../scanner.h"
#include "../../errno/errno.h"

int main(int argc, char **argv)
try
{
    Scanner scanner(argv[1]);

    while (true)
    {
        Scanner::Token t = scanner.lex();

        if (t == Scanner::ENDFILE)
            break;

        cout << "Token " << t << ": " << scanner.text() << endl;
    }
    return 0;
}
catch (Errno const &err)
{
    cout << err.what() << " (" << err.which() << ")" << endl;
    return 1;
}
