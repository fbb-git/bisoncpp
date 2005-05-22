#include "scanner.ih"

void Scanner::octal()
{
    istringstream istr(yytext + 2);
    istr >> oct >> d_number;

    if (d_number > 0xff)
        lineMsg() << "Quoted constant " << yytext << " exceeds 0177" << 
                        err;
}
