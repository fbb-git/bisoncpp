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
    while (cin.get(c) && (c == ' ' || c == '\t'))
        ;

    if (!cin)                   // no characters were obtained
        return 0;                   // indicate End Of Input  
    
    if (c == '.' || isdigit (c))    // if a digit char was found
    {
        cin.putback(c);        // return the character
        cin >> d_val__.u_val;    // extract a number
        return NUM;                 // return the NUM token
    }
    
    if (!isalpha(c))                // c doesn't start an identifier: 
        return c;                   // return a single character token.

    // in all other cases, an ident is entered. Recognize a var or function

    string word;           // store the name in a string object

    while (true)                // process all alphanumerics:
    {
        word += c;              // add 'm to `word'
        if (!cin.get(c))   // no more chars? then done here
            break;

        if (!isalnum(c))        // not an alphanumeric: put it back and done.
        {
            cin.putback(c);
            break;
        }
    }
                                // Now lookup the name as a function's name
    unordered_map<string, double (*)(double)>::iterator function = 
                                                s_functions.find(word);

                                // Got it, so return FPTR 
    if (function != s_functions.end())  
    {
        d_val__.u_fun = function->second;
        return FNCT;
    }
                                // no function, so return a VAR. Set
                                // u_symbol to the symbol's address in the
                                // d_symbol map. The map will add the
                                // symbol if not yet there.
    d_val__.u_symbol = &d_symbols[word];
    return VAR;            
}
