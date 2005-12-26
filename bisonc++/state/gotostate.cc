#include "state.ih"

unsigned State::gotoState(NonTerminal const *symbol) const
{
    GoToTableConstIter element = d_goto.find(symbol);

    return element == d_goto.end() ? UINT_MAX : element->second;
}
