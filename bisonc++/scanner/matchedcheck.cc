#include "scanner.ih"

    // called from lexer's action when the xstring mini scanner terminates.
    // if nKept != 0, determine *nKept as the number of trailing blanks

int Scanner::matchedCheck(size_t minLength, int retToken)
{
    size_t pos = d_matched.find_last_not_of(" \t");
    d_nKept = pos + 1;

    if (d_include)
        return 0;                       // from an %include: lex doesn't ret

    return pos < minLength ? ' ' : retToken;
}


