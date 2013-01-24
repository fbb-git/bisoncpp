/*
                              driver.cc
*/

#include "driver.h"

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
}
catch (exception const &err)
{
    cout << err.what() << " (" << errno << ")" << endl;
    return 1;
}
