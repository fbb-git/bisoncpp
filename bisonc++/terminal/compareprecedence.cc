#include "terminal.ih"

Terminal::Precedence
    Terminal::comparePrecedence(Symbol const *firstSymbol, 
                                Symbol const *secondSymbol)
{
    Terminal const *first = downcast(firstSymbol);
    Terminal const *second = downcast(secondSymbol);

    size_t firstPrecedence = first ? first->d_precedence : 0;
    size_t secondPrecedence = second ? second->d_precedence : 0;

    return firstPrecedence > secondPrecedence ?
                LARGER 
            : firstPrecedence < secondPrecedence ?
                SMALLER
            :
                EQUAL;
}
