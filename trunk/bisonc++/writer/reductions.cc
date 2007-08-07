#include "writer.ih"

void Writer::reductions(Table &table, State const &state)
{
    for 
    (
        size_t idx = 0, 
                defaultReduction = state.defaultReduction(),
                nReductions = state.reductions();
            idx != nReductions;
                ++idx
    )
    {
        if (idx != defaultReduction)
            reduction(table, *state.reduction(idx));
    }
}
