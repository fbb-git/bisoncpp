#include "scanner.ih"

    // remove the "..." or <...> delimiters from the text in yytext
void Scanner::undelimit(bool warn)
{
    if (strchr("\"<", yytext[0]) == 0)
        return;

    if (warn && yytext[0] == '<')
        lineMsg() << "<...> delimiters interpreted as \"...\"" << warning;

    yytext[yyleng - 1] = 0;                     // remove the last delimiter
    memmove(yytext, yytext + 1, yyleng - 1);    // shiftleft 1 all bytes
}
