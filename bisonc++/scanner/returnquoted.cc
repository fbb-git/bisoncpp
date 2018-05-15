#include "scanner.ih"

void Scanner::returnQuoted(void (Scanner::*handler)())
{
    if (d_block)
    {
        d_block += d_matched;   
        begin(StartCondition_::block);
    }
    else
    {
        begin(StartCondition_::INITIAL);
        (this->*handler)();         // handles quoted 
                                    //          octal constant  (octal) or
                                    //          hex constant    (hexadecimal)
                                    // why not escape sequence? (escape)
  
        leave(Parser::QUOTE);
    }
}
