#include "scanner.ih"

    // remove the "..." or <...> delimiters from the text in d_matched
void Scanner::undelimit(bool warn)
{
                                    // string does not start with " or <
    if (string("\"<").find(d_matched[0]) == string::npos)
        return;

    if (warn && d_matched[0] == '<')
        lineMsg(wmsg) << "<...> delimiters interpreted as \"...\"" << endl;

    setMatched(d_matched.substr(1, length() - 2));

    // yytext[yyleng - 1] = 0;                     // remove the last delimiter
    // memmove(yytext, yytext + 1, yyleng - 1);    // shiftleft 1 all bytes
}
