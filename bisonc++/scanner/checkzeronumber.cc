#include "scanner.ih"

void Scanner::checkZeroNumber() 
{
    if (d_number == 0)
        lineMsg(emsg) << "Quoted constant " << yytext << " equals zero" << 
                                                                        endl;
}
