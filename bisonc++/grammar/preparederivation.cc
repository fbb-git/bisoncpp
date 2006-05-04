#include "grammar.ih"

void Grammar::prepareDerivation()
{
    for_each(State::begin(), State::end(), 
        Wrap1c<State, Grammar>(insert, *this));
}
