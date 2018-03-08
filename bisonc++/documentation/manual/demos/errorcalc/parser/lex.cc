#include "Parser.ih"

/*
    Lexical scanner returns a double floating point 
    number on the stack and the token NUM, or the ASCII
    character read if not a number.  Skips all blanks
    and tabs, returns 0 for EOF.
*/

int Parser::lex()
{
    char c;
                                    // get the next non-ws character
    while (std::cin.get(c) && c == ' ' || c == '\t')            
        ;

    if (!std::cin)                   // no characters were obtained
        return 0;                   // indicate End Of Input  
    
    if (c == '.' || isdigit (c))    // if a digit char was found
    {
        std::cin.putback(c);        // return the character
        std::cin >> d_val;          // extract a number
        return NUM;                 // return the NUM token
    }

    return c;                       // otherwise return the extracted char.
}
