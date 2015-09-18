#include "rules.hh"

void Rules::updatePrecedence(Production *production, 
                             Terminal::Vector const &tv)
{   
    if (production->precedence())       // a precedence has already been set
        return;

    auto symbolIter = 
        find_if(production->begin(), production->end(), isTerminal);

    if (symbolIter != production->end())
        production->setPrecedence(Terminal::downcast(*symbolIter));
}
