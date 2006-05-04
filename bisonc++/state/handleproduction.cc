#include "state.ih"

void State::handleProduction(Production const *production, State &state)
{
    state.handle(Item(production, 0));
}


