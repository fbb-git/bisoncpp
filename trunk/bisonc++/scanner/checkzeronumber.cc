#include "scanner.ih"

void Scanner::checkZeroNumber() 
{
    if (d_number == 0)
        lineMsg() << "Quoted constant " << yytext << " equals zero" << err;
}
