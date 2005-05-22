#include "state.ih"

void State::addIfSymbolAt0(Production const *production, 
                    AISA0Context &context)
{
    if (production->atIdx(0) == &context.symbol)
        *context.dest += Item(production, 1, context.lookaheadSet);
}
