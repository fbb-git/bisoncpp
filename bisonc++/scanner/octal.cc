#include "scanner.ih"

void Scanner::octal()
{
    istringstream istr(d_matched.substr(2));
    istr >> oct >> d_number;

    if (d_number > 0xff)
        emsg << "Quoted constant " << d_matched << " exceeds 0177" << endl;
    else 
        checkZeroNumber();
}
