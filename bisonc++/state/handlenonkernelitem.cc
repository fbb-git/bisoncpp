#include "state.ih"

void State::handleNonKernelItem(Symbol const *symbol)
{
    if (!d_transition[symbol]->productionsEntered())
    {
        d_transition[symbol]->enteredProductions();

        NonTerminal::ProdVect const &productions = 
                            NonTerminal::downcast(symbol)->productions();

        for_each(productions.begin(), productions.end(),
                Wrap1c<Production, State>(handleProduction, *this));
    }
}
