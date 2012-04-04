#include "scanner.ih"

void Scanner::returnQuoted(void (Scanner::*handler)())
{

// Remove the comment in the next 2 lines:
    if (d_block)                // .skip(d_matched))
        d_block += d_matched;   //  begin(StartCondition__::block);
    else
    {
        begin(StartCondition__::INITIAL);
        (this->*handler)();         // handles quoted 
                                    //          octal constant  (octal) or
                                    //          hex constant    (hexadecimal)
                                    // why not escape sequence? (escape)
  
        leave(Parser::QUOTE);
    }
}
