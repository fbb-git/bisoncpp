#include "scanner.ih"

//  Return the next series of non-blank characters, stops also at C or C++
// comment
char const *Scanner::nextString() 
{
    string collect;

    while (true)
    {
        switch (lex())
        {
            case WS:
            return (d_text = collect).c_str();

            case ENDFILE:
            unexpectedEOF();

            default:
                collect += yytext;
            continue;
        }
    }
}
