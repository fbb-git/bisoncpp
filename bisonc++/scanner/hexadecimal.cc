#include "scanner.ih"

void Scanner::hexadecimal()
{
    istringstream istr(d_matched.substr(3));
    istr >> hex >> d_number;

    checkZeroNumber();
}
