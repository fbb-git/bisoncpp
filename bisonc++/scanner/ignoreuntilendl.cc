#include "scanner.ih"

void Scanner::ignoreUntilEndl() 
{
    while (true)
    {
        d_retWS = true;
        switch (lex())
        {
            case WS:
                if (yytext[0] != '\n')
                    continue;
            case ENDFILE:
            return;
        }
    }
}
