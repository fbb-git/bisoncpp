#include "scanner.ih"

void Scanner::hexadecimal()
{
    istringstream istr(yytext + 3);
    istr >> hex >> d_number;

    checkZeroNumber();
}
