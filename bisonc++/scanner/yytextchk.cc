#include "scanner.ih"

    // called from lexer's action when the xstring mini scanner terminates.
    // if nKept != 0, determine *nKept as the number of trailing blanks

int Scanner::matchedCheck(size_t minLength, int retToken)
{
    size_t idx = length();

    size_t pos = d_matched.find_last_not_of(" \t");
        //while (idx-- && (d_matched[idx] == ' ' || d_matched[idx] == '\t'))
        //;

        // if ((idx > 0 || d_matched[0] != ' ') && d_matched[0] != '\t')
        // ++idx;
    
    d_nKept = idx;

    if (d_include)
        return 0;                       // from an %include: yylex doesn't ret

    return idx < minLength ? ' ' : retToken;
}


