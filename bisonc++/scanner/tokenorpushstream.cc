#include "scanner.ih"

Scanner::() const
{
    accept(length() - 2);
    
    begin(d_includeOnly ? StartCondition__::includeOnly : 
                          StartCondition__::INITIAL);

    d_ret = matchedCheck(1, Parser::STRING);
    accept(d_nKept);

    if (d_ret)
        return d_ret;
    
    pushSource();
}


